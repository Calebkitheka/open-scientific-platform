#pragma once
#include <vector>
#include <stdexcept>

struct Matrix {
    size_t rows;
    size_t cols;
    std::vector<double> data;

    Matrix(size_t r, size_t c);
    double& at(size_t r, size_t c);
    const double& at(size_t r, size_t c) const;
    
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    void print() const;
};