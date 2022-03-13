// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "SocketUtil.h"
using std::cerr;
using std::endl;
// print message
void Usage(char* progname);

// Create a listening socket, accept a connection from a client,
// and write all the data the client sends to stdout.
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }
  // Loop forever, accepting a connection from a client and doing
  // an echo trick to it.
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr*>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;
      cerr << "Failure on accept: " << strerror(errno) << std::endl;
      break;
    }
    // read and write message.
    unsigned char clientbuf[1024];
    int read = WrappedRead(client_fd, clientbuf, 1024);
    while (read != 0) {
      int res = WrappedWrite(STDOUT_FILENO, clientbuf, read);
      if (res != read) {
        std::cerr << "read and write mismatch" << endl;
        break;
      }
      read = WrappedRead(client_fd, clientbuf, 1024);
    }
  }
  // Close up shop.
  // close(STDOUT_FILENO);
  close(listen_fd);
  return EXIT_SUCCESS;
}
void Usage(char* progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}
