#pragma once

#include <iostream>
#include <math.h>

class Vec2 {
public:
    float x, y;

    Vec2(float x, float y);

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator+(const float rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator-(const float rhs) const;
    Vec2 operator*(const Vec2& rhs) const;
    Vec2 operator*(const float rhs) const;
    Vec2 operator/(const Vec2& rhs) const;
    Vec2 operator/(const float rhs) const;
    Vec2 operator+=(const Vec2& rhs);
    Vec2 operator+=(const float rhs);
    Vec2 operator-=(const Vec2& rhs);
    Vec2 operator-=(const float rhs);
    Vec2 operator*=(const Vec2& rhs);
    Vec2 operator*=(const float rhs);
    Vec2 operator/=(const Vec2& rhs);
    Vec2 operator/=(const float rhs);

    float magnitude();
    void normalize();
    Vec2 normalized();
    float dot(const Vec2& other);
    void rotateRad(float radians);
    void rotateDeg(float degrees);
    void print();
};