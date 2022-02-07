#include "Vector.h"

// default constructor
Vector::Vector(){
    x_ = 0;
    y_ = 0;
    z_ = 0;
}
// constructor with three arguments
Vector::Vector(const float x, const float y, const float z) {
    x_ = x;
    y_ = y;
    z_ = z;
}
// copy constructor
Vector::Vector(const Vector& copyme) {
    x_ = copyme.x_;
    y_ = copyme.y_;
    z_ = copyme.z_;
}
//
Vector& Vector::operator=(const Vector& rhs) {
    if (this != &rhs) {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
    }
    return *this;
}
Vector& Vector::operator+=(const Vector& rhs) {
    if (this != &rhs) {
        x_ = rhs.x_ + x_;
        y_ = rhs.y_ + y_;
        z_ = rhs.z_ + z_;
    }
    return *this;
}
Vector& Vector::operator-=(const Vector& rhs) {
    if (this != &rhs) {
        x_ = x_ - rhs.x_;
        y_ = y_ - rhs.y_;
        z_ = z_ - rhs.z_;
    }
    return *this;
}
float Vector::operator*(const Vector& rhs) {
    if (this != &rhs) {
        return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_;
    }
}