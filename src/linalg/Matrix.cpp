#include <iostream> 
#include <vector> 
#include <stdexcept>
#include <cmath>
#include <Windows.h>

using namespace std;

class Matrix {
private:
    size_t rows_;
    size_t cols_;
    vector<double> data_;

public:
    Matrix(size_t rows, size_t cols)
        :rows_(rows), cols_(cols), data_(rows*cols) {

        }

    size_t rows() const noexcept { return rows_; }
    size_t cols() const noexcept { return cols_; }

    bool is_squared() const {
        return rows_ == cols_;
    }

    bool is_zero() const {
        for (double value : data_) {
            if(abs(value) > 1e-12) {
                return false;
            }
        }
        return true;
    }

    void print() const {
        cout << "rows: " << rows_ <<
        "\tcolumns: " << cols_ << endl;
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

            for(size_t i=0; i < rows(); i++) {
                for(size_t j=0; j < cols(); j++) {
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

            for(size_t i=0; i < rows(); i++) {
                for(size_t j=0; j < cols(); j++) {
                    result(i, j) = (*this)(i, j) - other(i,j);
                }
            }
            return result;
                
        }

    Matrix operator*(const Matrix& other) const {
            if(cols() != other.rows()) {
                throw invalid_argument("matrix dimensions are incompatible for multiplication");
            }
            Matrix result(rows(), other.cols());

            for(size_t i=0; i < rows(); i++) {
                for(size_t j=0; j < other.cols(); j++) {
                    double sum = 0.0;
                    for(size_t k=0; k < cols(); k++) {
                        sum += (*this)(i, k)*other(k, j);
                    }
                    result(i, j) = sum;
                }
            }
            return result;
        }

    Matrix operator*(double scalar) const {
        Matrix result(rows(), cols());

            for(size_t i=0; i < rows(); i++) {
                for(size_t j=0; j < cols(); j++) {
                    result(i, j) = (*this)(i, j) * scalar;
                }
            }
            return result;
                
        }

};

Matrix operator*(const double scalar, const Matrix& m) {
    return m * scalar;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Matrix matrix(3, 5);
    matrix.print();
    cout << (matrix.is_squared() ? "Yes" : "No") << endl;
}