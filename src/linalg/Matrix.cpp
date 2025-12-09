#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <algorithm>

#include "Vector.cpp";

using namespace std;

class Matrix {
private:
    size_t rows_;
    size_t cols_;
    vector<double> data_;
    static constexpr double EPS = 1e-12;

public:
    Matrix(size_t rows, size_t cols)
        :rows_(rows), cols_(cols), data_(rows*cols) {

        }

    size_t rows() const noexcept { return rows_; }
    size_t cols() const noexcept { return cols_; }

    bool is_squared() const {
        return rows_ == cols_; }

    bool is_zero() const {
        for (double value : data_) {
            if(abs(value) > 1e-12) {
                return false;
            }
        }
        return true;
    }

    Matrix transpose() const {
        Matrix result(cols(), rows());

        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    void fill(double value) {
        std::fill(data_.begin(), data_.end(), value);
        return;
    }

    static Matrix identity(size_t n) {
        Matrix result(n, n);

        for(size_t i=0; i < n; ++i) {
            result(i, i) = 1.0;
        }
        return result;
    }

    double& operator()(size_t i, size_t j) {
        if(i >= rows_ || j >= cols_) {
            throw out_of_range("matrix index out of bounds");
        } else {
            return data_[i*cols_+j];
        }
        
    }

    const double& operator()(size_t i, size_t j) const {
        if(i >= rows_ || j >= cols_) {
            throw out_of_range("matrix index out of bounds");
        } else {
            return data_[i*cols_+j];
        }
    }

    Matrix operator+(const Matrix& other) const {
        if(cols() != other.cols() || rows() != other.rows()) {
            throw invalid_argument("matrix dimensions are incompatible for addition");
        }
        Matrix result(rows(), cols());

        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                result(i, j) = (*this)(i, j) + other(i,j);
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if(cols() != other.cols() || rows() != other.rows()) {
            throw invalid_argument("matrix dimensions are incompatible for subtraction");
        }
        Matrix result(rows(), cols());

        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                result(i, j) = (*this)(i, j) - other(i,j);
            }
        }
        return result;   
    }

    Matrix operator-() const {
        return (*this) * (-1.0);
    }

    Matrix operator*(const Matrix& other) const {
        if(cols() != other.rows()) {
            throw invalid_argument("matrix dimensions are incompatible for multiplication");
        }
        Matrix result(rows(), other.cols());

        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < other.cols(); ++j) {
                double sum = 0.0;
                for(size_t k=0; k < cols(); ++k) {
                    sum += (*this)(i, k)*other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result(rows(), cols());

        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                result(i, j) = (*this)(i, j) * scalar;
            }
        }
        return result;     
    }

    bool operator==(const Matrix& other) const {
        if(cols() != other.cols() || rows() != other.rows()) {
            return false;
        }
        
        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                if (abs((*this)(i, j) - other(i, j)) > EPS) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other); }

    Matrix& operator+=(const Matrix& other) {
        if(cols() != other.cols() || rows() != other.rows()) {
            throw invalid_argument("matrix dimensions are incompatible for addition");
        }
        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                (*this)(i, j) += other(i,j);
            }
        }

        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        if(cols() != other.cols() || rows() != other.rows()) {
            throw invalid_argument("matrix dimensions are incompatible for subtraction");
        }
        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                (*this)(i, j) -= other(i,j);
            }
        }
        
        return *this;
    }

    Matrix& operator*=(double scalar) {
        for(size_t i=0; i < rows(); ++i) {
            for(size_t j=0; j < cols(); ++j) {
                (*this)(i, j) *= scalar;
            }
        }
        return *this;

    }

    Vector operator*(const Vector& v) const {
        if(cols() != v.size()) {
            throw invalid_argument("matrix columns must equal vector size");
        }
        Vector result(rows());
        for(size_t i=0; i < rows(); ++i) {
            double sum = 0.0;
            for(size_t j=0; j < cols(); ++j) {
                sum += (*this)(i,j) * v[j];
            }
            result[i] = sum;
        }
        return result;
    }

};

Matrix operator*(const double scalar, const Matrix& m) {
    return m * scalar;
}

ostream& operator<<(ostream& os, const Matrix& m) {
    for(size_t i=0; i < m.rows(); ++i) {
        for(size_t j=0; j < m.cols(); ++j) {
            os << m(i, j);
            if (j + 1 < m.cols()) os << "\t";
        }
        os << "\n";
    }
    return os;
}

int main() {

}