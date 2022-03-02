// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstdlib>

using std::cout;
using std::map;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::pair;

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations

// read and count individual strings in the file
template <typename T> bool ReadValue(ifstream& in, T* output);
// print the pair (first print key then print value)
void PrintOut(const pair<string, int>& p);

//////////////////////////////////////////////////////////////////////////////
// Main
//
int main(int argc, char* argv[]) {
  map<string, int>::iterator it;
  map<string, int> map;
  if (argc != 2) {
    cerr << "Usage: ./ex8 filename" << endl;
    return EXIT_FAILURE;
  }
  string line;
  ifstream myfile;
  myfile.open(argv[1]);
  if (myfile.is_open()) {
    
    while (ReadValue(myfile, &line)) {
      it = map.find(line);
      if(it == map.end()) {
        map[line] = 1;
      } else {
        map[line] += 1;
      }
    }
    for_each(map.begin(), map.end(), &PrintOut);
    myfile.close();

  } else {
    cout << "Unable to open file";
    return EXIT_FAILURE;
  }

  
  return EXIT_SUCCESS;
}

template <typename T>
bool ReadValue(ifstream& in, T* output) {
  if (!in.eof()) {
    in >> * output;
    if (in.fail()) {
      return false;
    }
    return true;
  } else{
    return false;
  }
}

void PrintOut(const pair<string, int>& p) {
  cout << p.first << " " << p.second << endl;
}


