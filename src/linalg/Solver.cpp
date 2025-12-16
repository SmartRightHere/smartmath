#include <cmath>

#include "Matrix.hpp"; // -I include/

static constexpr double EPS = 1e-8;

Vector sigm(const Vector& z) {
    Vector sigm_z(z.size());
    for(size_t i=0; i < z.size(); ++i) {
        if(z[i] > 0) {
            sigm_z[i] = 1.0/(1.0+exp(-z[i]));
        } else {
            sigm_z[i] = exp(z[i])/(1.0+exp(z[i]));
        }   
    }
    return sigm_z;
}

double log_loss(const Matrix& X, const Vector& w,
                const Vector& y) {
    static constexpr double EPS = 1e-15;
    if(X.cols() != w.size() || X.rows() != y.size()) {
        throw std::invalid_argument("X.cols() must equal w.size() and X.rows() must equal y.size()");
    }
    
    size_t n = X.rows();
    Vector y_pred = X * w;
    Vector p = sigm(y_pred);

    double total_loss = 0.0;
    for(size_t i=0; i < p.size(); ++i) {
        if(y[i] != 0.0 && y[i] != 1.0) {
            throw std::invalid_argument("y[i] must be 0.0 or 1.0 for logistic regression");
        }

        double p_clip = p[i];
        if(p_clip < EPS) {
            p_clip = EPS;
        } else if(p_clip > 1.0-EPS) {
            p_clip = 1.0-EPS;
        }
        
        double loss_i = -(y[i] * std::log(p_clip)
                    + (1.0-y[i]) * std::log(1.0-p_clip));
        total_loss += loss_i;
    }

    return total_loss/n;
}

Vector log_grad(const Matrix& X, const Vector& w,
                const Vector& y) {
    if (X.cols() != w.size() || X.rows() != y.size()) {
        throw std::invalid_argument("X.cols() must equal w.size() and X.rows() must equal y.size()");
    }
    Vector p = sigm(X * w);
    Vector err = p - y;
    Vector grad_raw = X.transpose() * err;
    return (1.0/X.rows()) * grad_raw;
}

double mse_loss(const Matrix& X, const Vector& w,
                const Vector& y) {
    if(X.cols() != w.size() || X.rows() != y.size()) {
        throw std::invalid_argument("X.cols() must equal w.size() and X.rows() must equal y.size()");
    }
    
    size_t n = X.rows();
    Vector y_pred = X * w;
    Vector err = y - y_pred;

    return dot(err, err)/n;
}

Vector mse_grad(const Matrix& X, const Vector& w,
                const Vector& y) {
    if(X.cols() != w.size() || X.rows() != y.size()) {
        throw std::invalid_argument("X.cols() must equal w.size() and X.rows() must equal y.size()");
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

Vector ridge_regression(const Matrix& X, const Vector& y,
        double alpha = 0.1, size_t epochs = 1000,
        double learn_rate = 0.01) {
    Vector w(X.cols());
    for(size_t i=0; i < epochs; ++i) {
        Vector grad = mse_grad(X, w, y) + 2 * alpha * w;
        Vector delta = learn_rate * grad;

        double norm_sq = dot(delta, delta);
        if(norm_sq < EPS * EPS) {
            break;
        }
        w -= delta;
    }

    return w;
}

Vector lasso_regression(const Matrix& X, const Vector& y,
        double alpha = 0.1, size_t epochs = 1000,
        double learn_rate = 0.01) {
    Vector w(X.cols());
    for(size_t i=0; i < epochs; ++i) {
        Vector sign_w(X.cols());
        for(size_t j=0; j < X.cols(); ++j) {
            if(w[j] > 0) {
                sign_w[j] = 1.0;
            } else if(w[j] < 0.0) {
                sign_w[j] = -1.0;
            } else {
                sign_w[j] = 0.0;
            }
        }
        Vector grad = mse_grad(X, w, y) + alpha * sign_w;
        Vector delta = learn_rate * grad;

        double norm_sq = dot(delta, delta);
        if(norm_sq < EPS * EPS) {
            break;
        }
        w -= delta;
    }

    return w;
}