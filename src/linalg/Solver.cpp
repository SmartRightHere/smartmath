#include <iostream>
#include <cassert>
#include <cmath>

#include "Matrix.hpp"; // -I include/

static constexpr double EPS = 1e-8;

double mse_loss(const Matrix& X, const Vector& w,
                const Vector& y) {
    if(X.cols() != w.size() || X.rows() != y.size()) {
        throw std::invalid_argument("matrix columns must equal vector size");
    }
    
    size_t n = X.rows();
    Vector y_pred = X * w;
    Vector err = y - y_pred;

    return dot(err, err)/n;
}

Vector mse_grad(const Matrix& X, const Vector& w,
                    const Vector& y) {
    if(X.cols() != w.size() || X.rows() != y.size()) {
        throw std::invalid_argument("matrix columns must equal vector size");
    }
    
    size_t n = X.rows();
    Vector y_pred = X * w;
    Vector err = y_pred - y;
    Vector grad = (2.0/n) * X.transpose() * err;

    return grad;
}

Vector grad_reg(const Matrix& X, const Vector& y,
                size_t epochs = 1000, double learn_rate = 0.01) {
    Vector w(X.cols());
    for(size_t i=0; i < epochs; ++i) {
        Vector grad = mse_grad(X, w, y);
        Vector delta = learn_rate * grad;

        double norm_sq = dot(delta, delta);
        if(norm_sq < EPS * EPS) {
            break;
        }
        w -= delta;
    }

    return w;
}