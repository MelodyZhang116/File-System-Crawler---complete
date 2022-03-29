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

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;

namespace hw3 {

QueryProcessor::QueryProcessor(const list<string>& index_list, bool validate) {
  // Stash away a copy of the index list.
  index_list_ = index_list;
  array_len_ = index_list_.size();
  Verify333(array_len_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader* [array_len_];
  itr_array_ = new IndexTableReader* [array_len_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = index_list_.begin();
  for (int i = 0; i < array_len_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < array_len_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t doc_id;  // The document ID within the index file.
  int     rank;    // The rank of the result so far.
} IdxQueryResult;

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string>& query) const {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> final_result;
  int length = query.size();
  // traverse each index file
  for (int i = 0; i < array_len_; i++) {
    // process the first word in the index file
    DocIDTableReader* docID_reader = itr_array_[i]->LookupWord(query[0]);
    // if the word is not found in the index file, search next index file
    if (docID_reader == nullptr) {
      continue;
    }
    // found the word in the index file, default (query[0]) list
    list<DocIDElementHeader> docID_elements = docID_reader->GetDocIDList();
    delete docID_reader;
    // process the rest of the word
    for (int j = 1; j < length; j++) {
      DocIDTableReader* docID_reader = itr_array_[i]->LookupWord(query[j]);
      // the word not found, search next index file
      if (docID_reader == nullptr) {
        docID_elements.clear();
        break;
      }
      list<DocIDElementHeader> new_list = docID_reader->GetDocIDList();
      delete docID_reader;
      // filter the list
      list<DocIDElementHeader>::iterator it;
      list<DocIDElementHeader>::iterator new_it;
      // iterate the default list, check if any doc_id match
      for (it = docID_elements.begin(); it != docID_elements.end(); it++) {
        for (new_it = new_list.begin(); new_it != new_list.end(); new_it++) {
          // doc_id match, update rank, search next default element
          if ((*new_it).doc_id == (*it).doc_id) {
            (*it).num_positions += (*new_it).num_positions;
            break;
          }
        }
        // no doc_id match, erase the element from the original list
        if (new_it == new_list.end()) {
          it = docID_elements.erase(it);
          it--;
        }
      }
    }

    // append current index file result
    for (DocIDElementHeader header : docID_elements) {
      QueryResult result;
      string file_name;
      dtr_array_[i]->LookupDocID(header.doc_id, &file_name);
      result.document_name = file_name;
      result.rank = header.num_positions;
      final_result.push_back(result);
    }
  }

  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

}  // namespace hw3
