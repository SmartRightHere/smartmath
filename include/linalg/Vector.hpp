#pragma once

#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <cmath>

class Vector {
private:
    std::vector<double> data_;
    static constexpr double EPS = 1e-12;

public:
    Vector(std::size_t n);
    Vector(std::initializer_list<double> list);

    std::size_t size() const noexcept;

    double& operator[](std::size_t i);
    const double& operator[](std::size_t i) const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator-() const;
    Vector operator*(double s) const;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(double s);
};

Vector operator*(double s, const Vector& v);
double dot(const Vector& a, const Vector& b);
double norm(const Vector& v);