// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::setw;

// This program will prompt user to input a positive integer,
// and print out its factors.
int main(int argc, char** argv) {
  string usage("Usage: ./ex5, with no additional argument pass in.");
  string prompt("Which positive integer would you like me to factorize? ");
  string message("Invalid input, please input a positive integer.");
  // If user input additional argument when execute, print the usage of
  // the program and exit.
  if (argc != 1) {
    cerr << usage << endl;
    return EXIT_FAILURE;
  }
  int num;
  cout << prompt;
  cin >> num;
  // If user input an invalid input, print the error message and exit.
  if (cin.get() != '\n' || num <= 0) {
    cerr << message << endl;
    return EXIT_FAILURE;
  }
  for (int i = 1; i < num; i++) {
    if (num % i == 0) {
      cout << i << " ";
    }
  }
  cout << num << endl;
}

