// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu
#include "Vector.h"
#include <iostream>
namespace cse333 {
Vector::Vector() {
    mag_ = new float[3];
    mag_[0] = 0.0;
    mag_[1] = 0.0;
    mag_[2] = 0.0;
}

Vector::Vector(const float x, const float y, const float z) {
    mag_ = new float[3];
    mag_[0] = x;
    mag_[1] = y;
    mag_[2] = z;
}

Vector::Vector(const Vector& v) {
    mag_ = new float[3];
    mag_[0] = v.mag_[0];
    mag_[1] = v.mag_[1];
    mag_[2] = v.mag_[2];
}

Vector::~Vector() {
    delete [] mag_;
}

Vector& Vector::operator=(const Vector& v) {
    if (this == &v) {
        return *this;
    }
    mag_[0] = v.mag_[0];
    mag_[1] = v.mag_[1];
    mag_[2] = v.mag_[2];
    return *this;
}

Vector& Vector::operator+=(const Vector& v) {
    mag_[0] += v.mag_[0];
    mag_[1] += v.mag_[1];
    mag_[2] += v.mag_[2];
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    mag_[0] -= v.mag_[0];
    mag_[1] -= v.mag_[1];
    mag_[2] -= v.mag_[2];
    return *this;
}

float Vector::operator*(const Vector& v) const {
    float result = (mag_[0] * v.mag_[0] + mag_[1] *
                    v.mag_[1] + mag_[2] * v.mag_[2]);
    return result;
}

Vector operator*(const Vector& v, const float k) {
    Vector temp(v.mag_[0]*k, v.mag_[1]*k, v.mag_[2]*k);
    return temp;
}
Vector operator*(const float k, const Vector& v) {
    Vector temp(v.mag_[0]*k, v.mag_[1]*k, v.mag_[2]*k);
    return temp;
}

Vector operator+(const Vector& a, const Vector& b) {
    Vector temp = a;
    temp += b;
    return temp;
}
Vector operator-(const Vector& a, const Vector& b) {
    Vector temp = a;
    temp -= b;
    return temp;
}

std::ostream& operator<<(std::ostream& s, const Vector& v) {
    s << "(" << v.mag_[0] << "," << v.mag_[1] << "," << v.mag_[2] << ")";
    return s;
}
}  // namespace cse333
