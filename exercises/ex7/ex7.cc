// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu
#include <iostream>
#include <string>

#include "Vector.h"

static const float kX1 = 1;
static const float kX2 = 2;
static const float kY1 = 3;
static const float kY2 = 3.1;
static const float kZ1 = -2.5;
static const float kZ2 = 2.7;
static const float k = 3.5;

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using cse333::Vector;

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations

// Output the values of a Vector to std::cout in the format "(x, y, z)".
static void PrintVector(const Vector& v);

// print out the actual values and expectation of values,
// but users have to verify themselves.
static void VerifyVector(const Vector& v, const float x, const float y,
                         const float z, const string& msg);



//////////////////////////////////////////////////////////////////////////////
// Main
//
// Create several Vectors and test their operations
int main() {
  // test constructors
  Vector v1;
  VerifyVector(v1, 0, 0, 0, "default ctor");
  Vector v2(kX1, kY1, kZ1);
  VerifyVector(v2, kX1, kY1, kZ1, "3-arg ctor");
  Vector v3(v2);
  VerifyVector(v3, kX1, kY1, kZ1, "cctor");

  // test assignment (including chaining)
  Vector v4(kX2, kY2, kZ2);
  v1 = v3 = v4;
  VerifyVector(v3, kX2, kY2, kZ2, "op=");
  VerifyVector(v4, kX2, kY2, kZ2, "op= chaining");

  // test updating assignment (including chaining)
  v1 = v3 += v2;
  VerifyVector(v3, kX1+kX2, kY1+kY2, kZ1+kZ2, "op+=");
  VerifyVector(v1, kX1+kX2, kY1+kY2, kZ1+kZ2, "op+= chaining");
  v1 = v3 -= v2;
  VerifyVector(v3, kX2, kY2, kZ2, "op-=");
  VerifyVector(v1, kX2, kY2, kZ2, "op-= chaining");

  // test vector*vector assignment
  float dot_product = v2 * v3;
  cout << "dot product: " << dot_product << endl;
  cout << "expectation: " << kX1 * kX2 + kY1 * kY2 + kZ1 * kZ2 << endl;
  cout << endl;

  dot_product = v3 * v2;
  cout << "dot product: " << dot_product << endl;
  cout << "expectation: " << kX1 * kX2 + kY1 * kY2 + kZ1 * kZ2 << endl;
  cout << endl;


  // test vector*float
  float c = k;
  Vector result = v2 * c;
  VerifyVector(result, kX1 * k, kY1 * k, kZ1 * k,
                "dot product with vector * float");
  // test float*vector
  result = c * v2;
  VerifyVector(result, kX1 * k, kY1 * k, kZ1 * k,
                "dot product with float * vector");

  // test +
  result = v2 + v3;
  VerifyVector(result, kX1 + kX2, kY1 + kY2, kZ1 + kZ2, "+");
  // test -
  result = v2 - v3;
  VerifyVector(result, kX1 - kX2, kY1 - kY2, kZ1 - kZ2, "-");






  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void PrintVector(const Vector& v) {
  cout << v << endl;
}

static void VerifyVector(const Vector& v, const float x, const float y,
                         const float z, const string& msg) {
  // print the values of the Vector
  cout << msg << ": ";
  PrintVector(v);

  // print what is expected
  cout << "expectation: ";
  cout << "(" << x << "," << y << "," << z << ")" << endl;
  cout << endl;
}
