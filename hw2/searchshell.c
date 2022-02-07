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


//////////////////////////////////////////////////////////////////////////////
// Main
// you can input a directory name, enter a list of words (no more than 10000)
// as query, and the program will return a list of files which include all of
// your queries, ranking by total number of times they show up in that file.
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
  DocTable* table;
  MemIndex* index;
  char input[10000];
  char* string;
  char* token;
  LinkedList* result;
  SearchResult* payload;
  char* name;
  fprintf(stdout, "Indexing \'%s\'\n", argv[1]);
  if (!CrawlFileTree(argv[1], &table, &index)) {
    Usage();
  }

  fprintf(stdout, "enter query:\n");
  while (fgets(input, 10000, stdin) != NULL) {
    string = input;
    char* query[5000];
    int i = 0;
    while ((token = strtok_r(string, " ", &string))) {
      for (int j = 0; j < strlen(token); j++) {
        *(token+j) = tolower(*(token+j));
      }
      query[i] = token;
      i++;
    }
    char* ptr = strchr(query[i - 1], '\n');
    *ptr = '\0';
    result = MemIndex_Search(index, query, i);
    if (result != NULL) {
      LLIterator* it = LLIterator_Allocate(result);
      while (LLIterator_IsValid(it)) {
        LLIterator_Get(it, (void**)&payload);
        name = DocTable_GetDocName(table, payload->doc_id);
        fprintf(stdout, "  %s (%i)\n", name, payload->rank);
        LLIterator_Next(it);
      }
      LLIterator_Free(it);
    }
    fprintf(stdout, "enter query:\n");
  }
  DocTable_Free(table);
  MemIndex_Free(index);
  LinkedList_Free(result, &free);
  fprintf(stdout, "shutting down...\n");
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
