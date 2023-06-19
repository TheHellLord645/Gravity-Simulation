#include <iostream>
#include <math.h>

class Vec2 {
public:
    float x, y;

    Vec2(float x, float y) :x(x), y(y) {}

    Vec2 operator+(const Vec2& rhs) const {
        Vec2 temp(*this);
        temp += rhs;
        return temp;
    }

    Vec2 operator+(const float rhs) const {
        Vec2 temp(*this);
        temp += rhs;
        return temp;
    }

    Vec2 operator-(const Vec2& rhs) const {
        Vec2 temp(*this);
        temp -= rhs;
        return temp;
    }

    Vec2 operator-(const float rhs) const {
        Vec2 temp(*this);
        temp -= rhs;
        return temp;
    }

    Vec2 operator*(const Vec2& rhs) const {
        Vec2 temp(*this);
        temp *= rhs;
        return temp;
    }

    Vec2 operator*(const float rhs) const {
        Vec2 temp(*this);
        temp *= rhs;
        return temp;
    }

    Vec2 operator/(const Vec2& rhs) const {
        Vec2 temp(*this);
        temp /= rhs;
        return temp;
    }

    Vec2 operator/(const float rhs) const {
        Vec2 temp(*this);
        temp /= rhs;
        return temp;
    }

    Vec2 operator+=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2 operator+=(const float rhs) {
        x += rhs;
        y += rhs;
        return *this;
    }

    Vec2 operator-=(const Vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2 operator-=(const float rhs) {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    Vec2 operator*=(const Vec2& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vec2 operator*=(const float rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vec2 operator/=(const Vec2& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Vec2 operator/=(const float rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    float magnitude() {
        return sqrt(x * x + y * y);
    }

    void normalize() {
        x /= magnitude();
        y /= magnitude();
    }

    Vec2 normalized() {
        return Vec2(x / magnitude(), y / magnitude());
    }

    float dot(const Vec2& other) {
        return x * other.x + y * other.y;
    }

    void rotateRad(float radians) {
        x = x * cos(radians) - y * sin(radians);
        y = x * sin(radians) + y * cos(radians);
    }

    void rotateDeg(float degrees) {
        degrees *= 3.14 / 180;
        x = x * cos(degrees) - y * sin(degrees);
        y = x * sin(degrees) + y * cos(degrees);
    }

    void print() {
        std::cout << "x: " << x << " y: " << y << '\n';
    }
};