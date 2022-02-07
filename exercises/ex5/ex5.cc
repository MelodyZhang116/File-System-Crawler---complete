// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu
#include <iostream>
#include <cstdlib>
#include <string>
using std::cout;
using std::string;
using std::cin;
using std::cerr;
using std::endl;
using std::__cxx11::stoi;
// This function return the positive integer of string str.
// return the positive int if str is positive integer,
// return -1 if it is not positive int (return false
// if it is characters, numbers with decimal point, or 0,
// or mix of them)
int isPositiveInteger(string str);

// This program will prompt user to input a positive integer,
// and print out its factors.
int main(int argc, char** argv) {
    string usage("Usage: ./ex5\nWith no additional argument pass in.");
    string NonPositiveInt("Only positive integer is allowed. This might "
                        "be caused by characters, negative sign, 0 or "
                        "decimal point. "
                        "You should input a positive integer.");
    // If user input additional argument when execute, print the usage of
    // the program and exit.
    if (argc != 1) {
        cerr << usage << endl;
        return EXIT_FAILURE;
    }
    string input;
    cout << "Which positive integer would you like me to factorize? ";
    cin >> input;
    int number = isPositiveInteger(input);
    if (number == -1) {
        // If user input an invalid input (not a positive integer),
        // print the error message and exit.
        cerr << NonPositiveInt << endl;
        return EXIT_FAILURE;
    } else {
        cout << 1;
        int i;
        for (i=2; i <= number; i++) {
            if (number % i == 0) {
                cout << " "<< i;
            }
        }
        cout << endl;
    }
}
int isPositiveInteger(string str) {
    int length = str.length();
    for (int i = 0; i < length; i++) {
        if (isdigit(str[i]) == false) {
            return -1;  // when one non numeric value is found, return false
        }
    }
    int result = stoi(str);
    if (result == 0) {
        return -1;
    } else {
        return result;
    }
}
