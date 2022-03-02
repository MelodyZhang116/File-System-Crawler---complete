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
  
  for ( int i = 0; i < array_len_; i++){
    list<IdxQueryResult> temp_result;
    DocTableReader* dtr = dtr_array_[i];
    IndexTableReader* itr = itr_array_[i];
    DocIDTableReader* iidtr = itr->LookupWord(query[0]); // call delete
    if (iidtr == nullptr) {
      continue;
    }
    //dtr->LookupDocID
    list<DocIDElementHeader> result = iidtr->GetDocIDList();
    delete iidtr;
    list<DocIDElementHeader>::iterator it;
    for (it = result.begin(); it != result.end(); it++) {
      //char* filename;
      //boolean test = dtr->LookupDocID((*it).doc_id, filename);
      //Verify333(test == true);
      IdxQueryResult queryResult;
      queryResult.doc_id = (*it).doc_id;
      queryResult.rank = (*it).num_positions;
      temp_result.push_back(queryResult);
    }

    if (query.size() > 1) {
      for (int i = 1; i < query.size() ; i++){
        DocIDTableReader* id_reader = itr->LookupWord(query[i]); // call delete
        if (iidtr == nullptr) {
          temp_result.clear();
          break;
        }
        
        list<IdxQueryResult>::iterator itIdx;
        for (itIdx = temp_result.begin(); itIdx != temp_result.end(); itIdx ++) {
          list<DocPositionOffset_t> offset;
          if (!id_reader->LookupDocID((*itIdx).doc_id, &offset)){
            if (offset.size() == 0) {
              temp_result.erase(itIdx);
              itIdx --;
            }
          } else {
            temp_result.erase(itIdx);
            itIdx --;
          }
          
        }
        
      
      }
    }
    list<IdxQueryResult>::iterator idx;
    for (idx = temp_result.begin(); idx != temp_result.end(); idx ++) {
      string filename;
      bool test = dtr->LookupDocID((*idx).doc_id, *filename);
      Verify333(test == true);
      vector<QueryProcessor::QueryResult>::iterator itqr;
      for (itqr = final_result.begin(); itqr != final_result.end(); itqr ++) {
        if ((*itqr).document_name == filename){
          (*itqr).rank += (*idx).rank;
        }
      }
    
    }
  }

  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

}  // namespace hw3
