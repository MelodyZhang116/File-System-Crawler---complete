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

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600
#define SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);
static void ProcessQueries(DocTable* dt, MemIndex* mi);
static int GetNextLine(FILE* f, char** ret_str);
static int ParseString(char* string, char* parse[]);


//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.
  DocTable *doc_table;
  MemIndex *index;
  int res;
  printf("Indexing \'%s\'\n", argv[1]);
  res = CrawlFileTree(argv[1], &doc_table, &index);
  if (!res) {
    Usage();
  }
  ProcessQueries(doc_table, index);
  //scanf("%c", &query);
  printf("exit");
  MemIndex_Free(index);
  DocTable_Free(doc_table);
  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static void ProcessQueries(DocTable* dt, MemIndex* mi) {
  char* query;
  int test;
  char* parse[SIZE];
  int length;
  LinkedList* ll_res;
  test = GetNextLine(stdin, &query);
  // query = "my name"; //
  printf("%s\n", query); //
  while (test != 0) {
    length = ParseString(query, parse);
    ll_res = MemIndex_Search(mi, &query, length);
    if (ll_res == NULL) {
      test = GetNextLine(stdin, &query);
      continue;
    }
    printf("%d", LinkedList_NumElements(ll_res));
    LLIterator* iter = LLIterator_Allocate(ll_res);
    Verify333(iter != NULL);
    while (LLIterator_IsValid(iter)) {
      SearchResult* sr;
      char* filename;
      LLIterator_Get(iter, (LLPayload_t *)sr);
      filename = DocTable_GetDocName(dt, sr->doc_id);
      printf("%s, %d \n", filename, sr->rank);
    }
    LLIterator_Free(iter);
    LinkedList_Free(ll_res, &free);
    test--;
  }
}

static int GetNextLine(FILE* f, char** ret_str) {
  char* string = (char*)malloc(sizeof(char) * SIZE);
  Verify333(string != NULL);
  printf("enter query: ");
  char* result = fgets(string, SIZE, f);
  if (result == NULL) {
    free(string);
    return 0;
  } else {
    *ret_str = result;
    return 1;
  }
}

static int ParseString(char* string, char* parse[]) {
  char* token;
  char* copy = string;
  char* rest;
  int len;
  len = 0;
  while (1) {
    token = strtok_r(copy, " ", &rest);
    if (token == NULL) {
      break;
    }
    parse[len] = token;
    len++;
    copy = rest;
  }
  parse[len-1][strlen(parse[len-1])-1] = '\0';
  return len;
}
