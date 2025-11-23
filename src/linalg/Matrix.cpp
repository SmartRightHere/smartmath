#include <iostream> 
#include <vector> 
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

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    bool is_squared() {
        return rows_ == cols_;
    }

    void print() {
        cout << "rows: " << rows_ <<
        "\tcolumns: " << cols_ << endl;
    }

    double& operator()(size_t i, size_t j) {
        return data_[i*cols_+j];
    }

    const double& operator()(size_t i, size_t j) const {
        return data_[i*cols_+j];
    }

};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Matrix matrix(3, 5);
    matrix.print();
    cout << (matrix.is_squared() ? "Yes" : "No") << endl;
}