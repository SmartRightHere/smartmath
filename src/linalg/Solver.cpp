#include <iostream>
#include <cassert>
#include <cmath>

#include "Vector.cpp";
#include "Matrix.cpp";

double mse_loss(const Matrix& X, const Vector& w,
                const Vector& y) {
    if(X.cols() != w.size() || X.rows() != y.size()) {
        throw invalid_argument("matrix columns must equal vector size");
    }
    
    size_t n = X.rows();
    Vector y_pred = X * w;
    Vector err = y - y_pred;

    return dot(err, err)/n;
}