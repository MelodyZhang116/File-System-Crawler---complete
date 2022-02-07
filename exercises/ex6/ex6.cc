// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu
#include <iostream>
#include <cstdlib>
#include "Vector.h"
void Increment(Vector vec);
bool VerifyAddress(const Vector& vec, const void* const temp);
int main(int argc, char* argv[]) {
    Vector x;
    if (x.get_x() != 0 || x.get_y() != 0 || x.get_z() != 0) {
        std::cout << "default constructor fails" << std::endl;
        return EXIT_FAILURE;
    }
    Vector y(1, 2, 3);
    if (y.get_x() != 1 || y.get_y() != 2 || y.get_z() != 3) {
        std::cout << "constructor fails" << std::endl;
        return EXIT_FAILURE;
    }
    Vector z(y);
    if (z.get_x() != 1 || z.get_y() != 2 || z.get_z() != 3) {
        std::cout << "copy constructor fails" << std::endl;
        return EXIT_FAILURE;
    }
    Vector k(2, 4, 6);
    k = y;
    if (k.get_x() != 1 || k.get_y() != 2 || k.get_z() != 3) {
        std::cout << "operator = fails" << std::endl;
        return EXIT_FAILURE;
    }
    Vector m(1.5, 2.5, 3.5);
    k += m;
    if (k.get_x() != 2.5 || k.get_y() != 4.5 || k.get_z() != 6.5) {
        std::cout << "operator += fails" << std::endl;
        return EXIT_FAILURE;
    }
    k -= m;
    if (k.get_x() != 1 || k.get_y() != 2 || k.get_z() != 3) {
        std::cout << "operator -= fails" << std::endl;
        return EXIT_FAILURE;
    }
    if (k * m != 17) {
        std::cout << "operator * fails" << std::endl;
        return EXIT_FAILURE;
    }
    Increment(k);
    if (k.get_x() != 2 || k.get_y() != 3 || k.get_z() != 4) {
        std::cout << "Vector: pass-by-value" << std::endl;
    } else {
        std::cout << "Vector: pass-by-value" << std::endl;
    }
    if (VerifyAddress(k, &k)) {
        std::cout << "Ref: same address" << std::endl;
    } else {
        std::cout << "Ref: different address" << std::endl;
    }
    return EXIT_SUCCESS;
}
void Increment(Vector vec) {
    Vector temp(1, 1, 1);
    vec += temp;
}
bool VerifyAddress(const Vector& vec, const void* const temp) {
    return &vec == temp;
}
