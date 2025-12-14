#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>
#include <iosfwd>

#include "Vector.hpp"

class Matrix {
private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<double> data_;
    static constexpr double EPS = 1e-12;

public:
    Matrix(std::size_t rows, std::size_t cols);

    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;

    bool is_squared() const;
    bool is_zero() const;

    Matrix transpose() const;
    void fill(double value);

    static Matrix identity(std::size_t n);

    double& operator()(std::size_t i, std::size_t j);
    const double& operator()(std::size_t i, std::size_t j) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator-() const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);

    Vector operator*(const Vector& v) const;
};

Matrix operator*(double scalar, const Matrix& m);

std::ostream& operator<<(std::ostream& os, const Matrix& m);