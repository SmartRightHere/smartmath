#include <iostream> 
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <Windows.h>

using namespace std;

class Vector {
private:
    vector<double> data_;
    static constexpr double EPS = 1e-12;
public:
    Vector(size_t n) : data_(n) {}

    Vector(initializer_list<double> list)
        :data_(list) {
        
    }

    size_t size() const noexcept { return data_.size(); }

    double& operator[](size_t i) {
        if(i >= data_.size()) {
            throw out_of_range("vector index out of bounds");
        }
        return data_[i];
        
    }

    const double& operator[](size_t i) const {
        if(i >= data_.size()) {
            throw out_of_range("vector index out of bounds");
        } 
        return data_[i];
        
    }

    Vector operator+(const Vector& other) const {
        if(size() != other.size()) {
            throw invalid_argument("vector sizes are incompatible for addition");
        }

        Vector result(size());
        for(size_t i=0; i < size(); ++i) {
            result[i] = (*this)[i] + other[i];
        }

        return result;
    }

    Vector operator-(const Vector& other) const {
        if(size() != other.size()) {
            throw invalid_argument("vector sizes are incompatible for subtraction");
        }

        Vector result(size());
        for(size_t i=0; i < size(); ++i) {
            result[i] = (*this)[i] - other[i];
        }

        return result;
    }

    Vector operator-() const {
        return (*this) * (-1.0);
    }

    Vector operator*(double s) const {
        Vector result(size());
        for(size_t i=0; i < size(); ++i) {
            result[i] = (*this)[i] * s;
        }

        return result;
    }

    bool operator==(const Vector& other) const {
        if(size() != other.size()) {
            return false;
        }
        for(size_t i=0; i < size(); ++i) {
            if (abs((*this)[i] - other[i]) > EPS) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other); }


    Vector& operator+=(const Vector& other) {
        if(size() != other.size()) {
            throw invalid_argument("vector sizes are incompatible for addition");
        }
        for(size_t i=0; i < size(); ++i) {
            (*this)[i] += other[i];
        }

        return *this;
    }

    Vector& operator-=(const Vector& other) {
        if(size() != other.size()) {
            throw invalid_argument("vector sizes are incompatible for subtraction");
        }
        for(size_t i=0; i < size(); ++i) {
            (*this)[i] -= other[i];
        }

        return *this;
    }

    Vector& operator*=(double s) {
        for(size_t i=0; i < size(); ++i) {
            (*this)[i] *= s;
        }
        return *this;
    }

};

Vector operator*(double s, const Vector& other) {
    return other * s;
}

double dot(const Vector& a, const Vector& b) {
    if(a.size() != b.size()) {
        throw invalid_argument("vector sizes are incompatible for dot product");
    }
    double result = 0.0;
    for(size_t i=0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

double norm(const Vector& v) {
    return sqrt(dot(v, v));
}

int main() {

}