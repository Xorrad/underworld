#pragma once

#include <iostream>
#include <cmath>

template <typename T>
class Vec2 {
public:
    T x, y;

    // Constructors
    Vec2();
    Vec2(T x, T y);
    Vec2(const Vec2& other);

    // Assignment
    Vec2& operator=(const Vec2& other);

    // Arithmetic operators
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(T scalar) const;
    Vec2 operator/(T scalar) const;

    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator*=(T scalar);
    Vec2& operator/=(T scalar);

    // Comparison
    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    // Dot product
    T Dot(const Vec2& rhs) const;

    // Length
    T Length() const;

    // Normalization
    Vec2 Normalize() const;

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Casting
    template <typename U>
    explicit operator Vec2<U>() const;

    explicit operator tuim::vec2() const;
};

// Non-member scalar * vector
template <typename T>
Vec2<T> operator*(T scalar, const Vec2<T>& v);

// Hash function for unordered maps.
namespace std {
    template <typename T>
    struct hash<Vec2<T>> {
        std::size_t operator()(const Vec2<T>& v) const noexcept {
            std::size_t h1 = std::hash<T>{}(v.x);
            std::size_t h2 = std::hash<T>{}(v.y);
            return h1 ^ (h2 << 1);
        }
    };
}