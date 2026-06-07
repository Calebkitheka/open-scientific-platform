#include "matrix.hpp"
#include <iostream>
#include <iomanip>

Matrix::Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c, 0.0) {
    if (r == 0 || c == 0) throw std::invalid_argument("Dimensions must be > 0");
}

double& Matrix::at(size_t r, size_t c) {
    if (r >= rows || c >= cols) throw std::out_of_range("Index out of bounds");
    return data[r * cols + c];
}

const double& Matrix::at(size_t r, size_t c) const {
    if (r >= rows || c >= cols) throw std::out_of_range("Index out of bounds");
    return data[r * cols + c];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Dimension mismatch for +");
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) result.data[i] = data[i] + other.data[i];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Dimension mismatch for -");
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) result.data[i] = data[i] - other.data[i];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) throw std::invalid_argument("Inner dimensions must agree: A(" + std::to_string(rows) + "x" + std::to_string(cols) + ") * B(" + std::to_string(other.rows) + "x" + std::to_string(other.cols) + ")");
    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < cols; ++k) {
                sum += at(i, k) * other.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

void Matrix::print() const {
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << at(r, c);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}