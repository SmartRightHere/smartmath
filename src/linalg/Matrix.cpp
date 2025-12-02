#include <iostream> 
#include <vector> 
#include <stdexcept>
#include <cmath>
#include <assert.h>
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
                if (abs((*this)(i, j) - other(i, j)) > 1e-12) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other); }

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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // addition test
    Matrix A(2, 2); A(0,0)=1; A(0,1)=2; A(1,0)=3; A(1,1)=4;
    Matrix B = A + A;
    assert((B(0,0) == 2.0) && (B(1,1) == 8.0));

    // scalar multiplication test
    Matrix C = 2.0 * A;
    assert(C == B);

    // transposition test
    Matrix D = A.transpose();
    assert(D(0,1) == A(1,0));

    // exception test
    try {
        Matrix X(2, 3), Y(4, 5);
        auto Z = X * Y; // should throw an exception
        assert(false); // it shouldn't reach here
    } catch (const std::invalid_argument&) {
        // OK
    }
}