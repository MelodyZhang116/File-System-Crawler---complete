/*
 * Copyright ©2022 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;



namespace hw4 {

static const char* kHeaderEnd = "\r\n\r\n";
static const int kHeaderEndLen = 4;
static const int SIZE = 1024;

bool HttpConnection::GetNextRequest(HttpRequest* const request) {
  // Use WrappedRead from HttpUtils.cc to read bytes from the files into
  // private buffer_ variable. Keep reading until:
  // 1. The connection drops
  // 2. You see a "\r\n\r\n" indicating the end of the request header.
  //
  // Hint: Try and read in a large amount of bytes each time you call
  // WrappedRead.
  //
  // After reading complete request header, use ParseRequest() to parse into
  // an HttpRequest and save to the output parameter request.
  //
  // Important note: Clients may send back-to-back requests on the same socket.
  // This means WrappedRead may also end up reading more than one request.
  // Make sure to save anything you read after "\r\n\r\n" in buffer_ for the
  // next time the caller invokes GetNextRequest()!

  // STEP 1:
  size_t pos = buffer_.find(kHeaderEnd);
  if (pos == string::npos) {
    int test;
    unsigned char buf[SIZE];
    while (1) {
      test = WrappedRead(fd_, buf, SIZE);
      if (test == -1) {
        // error occur
        return false;
      } else if (test == 0) {
        break;
      } else {
        char* buf1 = reinterpret_cast<char*>(buf);
        buffer_.append(buf1, test);
        pos = buffer_.find(kHeaderEnd);
        if (pos != string::npos) {  // find \r\n\r\n
          break;
        }
      }
    }
  }
  pos = buffer_.find(kHeaderEnd);
  if (pos == string::npos) {
    return false;
  }
  string str = buffer_.substr(0, pos+kHeaderEndLen);
  *request = ParseRequest(str);
  if (request->uri()== "NULL") {
    return false;
  }
  buffer_ = buffer_.substr(pos+kHeaderEndLen);
  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse& response) const {
  string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         reinterpret_cast<const unsigned char*>(str.c_str()),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(const string& request) const {
  HttpRequest req("/");  // by default, get "/".
  // Plan for STEP 2:
  // 1. Split the request into different lines (split on "\r\n").
  // 2. Extract the URI from the first line and store it in req.URI.
  // 3. For the rest of the lines in the request, track the header name and
  //    value and store them in req.headers_ (e.g. HttpRequest::AddHeader).
  //
  // Hint: Take a look at HttpRequest.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for:
  // - Splitting a string into lines on a "\r\n" delimiter
  // - Trimming whitespace from the end of a string
  // - Converting a string to lowercase.
  //
  // Note: If a header is malformed, skip that line.

  // STEP 2:
  vector<string> lines;
  boost::split(lines, request, boost::is_any_of("\r\n"),
                boost::token_compress_on);
  for (size_t i = 0; i < lines.size(); i++) {
    boost::trim(lines[i]);
  }
  // first line
  vector<string> first;
  boost::split(first, lines[0], boost::is_any_of(" "),
               boost::token_compress_on);
  if (first[0] != "GET") {
    req.set_uri("NULL");
    return req;
  }
  req.set_uri(first[1]);
  for (size_t i = 1; i < lines.size() -1; i++) {
    vector<string> line;
    boost::split(line, lines[i], boost::is_any_of(":"),
                  boost::token_compress_on);
    if (line.size() != 2) {
      continue;
    } else {
      boost::trim(line[0]);
      boost::trim(line[1]);
      boost::to_lower(line[0]);
      req.AddHeader(line[0], line[1]);
    }
  }
  return req;
}

}  // namespace hw4
