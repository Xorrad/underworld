#include "Vec2.hpp"

// Constructors
template <typename T>
Vec2<T>::Vec2() : x(0), y(0) {}

template <typename T>
Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

template <typename T>
Vec2<T>::Vec2(const Vec2& other) : x(other.x), y(other.y) {}

template <typename T>
Vec2<T>& Vec2<T>::operator=(const Vec2& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

// Arithmetic
template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator*(T scalar) const {
    return Vec2(x * scalar, y * scalar);
}

template <typename T>
Vec2<T> Vec2<T>::operator/(T scalar) const {
    return Vec2(x / scalar, y / scalar);
}

template <typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator*=(T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

template <typename T>
Vec2<T>& Vec2<T>::operator/=(T scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

// Comparison
template <typename T>
bool Vec2<T>::operator==(const Vec2& rhs) const {
    return x == rhs.x && y == rhs.y;
}

template <typename T>
bool Vec2<T>::operator!=(const Vec2& rhs) const {
    return !(*this == rhs);
}

// Dot product
template <typename T>
T Vec2<T>::Dot(const Vec2& rhs) const {
    return x * rhs.x + y * rhs.y;
}

// Length
template <typename T>
T Vec2<T>::Length() const {
    return std::sqrt(x * x + y * y);
}

// Normalization
template <typename T>
Vec2<T> Vec2<T>::Normalize() const {
    T len = Length();
    if (len == 0) return Vec2(0, 0);
    return Vec2(x / len, y / len);
}

template <typename T>
template <typename U>
Vec2<T>::operator Vec2<U>() const {
    return Vec2<U>(static_cast<U>(x), static_cast<U>(y));
}

template <typename T>
Vec2<T>::operator tuim::vec2() const {
    return tuim::vec2(static_cast<int>(x), static_cast<int>(y));
}

// Non-member scalar * vector
template <typename T>
Vec2<T> operator*(T scalar, const Vec2<T>& v) {
    return Vec2<T>(v.x * scalar, v.y * scalar);
}

// Explicit instantiations
template class Vec2<int>;
template class Vec2<float>;
template class Vec2<double>;

template Vec2<int> operator*(int, const Vec2<int>&);
template Vec2<float> operator*(float, const Vec2<float>&);
template Vec2<double> operator*(double, const Vec2<double>&);
