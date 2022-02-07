#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {
    public:
        Vector();
        Vector(const float x, const float y, const float z);
        Vector(const Vector& copyme);
        ~Vector(){};
        Vector& operator=(const Vector& rhs);
        float get_x() const { return x_; }
        float get_y() const { return y_; }
        float get_z() const { return z_; }
        Vector& operator+=(const Vector& rhs);
        Vector& operator-=(const Vector& rhs);
        float operator*(const Vector& rhs);


    private:
        float x_;
        float y_;
        float z_;
};
#endif  // VECTOR_H_