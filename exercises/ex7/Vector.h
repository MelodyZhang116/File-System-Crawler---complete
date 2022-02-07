// Copyright 2022 Yansong Liu
// Name: Yansong Liu, Melody Zhang
// Email: yliu59@uw.edu, mzhang22@uw.edu
#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

namespace cse333 {
class Vector {
    public:
        Vector();
        Vector(const float x, const float y, const float z);
        Vector(const Vector& v);
        ~Vector();
        Vector& operator=(const Vector& v);
        Vector& operator+=(const Vector& v);
        Vector& operator-=(const Vector& v);
        float operator*(const Vector& v) const;
        friend Vector operator*(const Vector& v, const float k);
        friend Vector operator*(const float k, const Vector& v);
        friend std::ostream& operator<<(std::ostream& s, const Vector& v);
    private:
        float* mag_;
};
Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);

}
#endif  // VECTOR_H_