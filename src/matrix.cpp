#include "matrix.hpp"
#include <iostream>
#include <iomanip>

Matrix::Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c, 0.0) {
    if (r == 0 || c == 0) throw std::invalid_argument("Dimensions must be > 0");
}

double& Matrix::at(size_t r, size_t c) {
    if (r >= rows || c >= cols) throw std::out_of_range("Index out of bounds");
    return data[r * cols + c]; // Row-major indexing
}

const double& Matrix::at(size_t r, size_t c) const {
    if (r >= rows || c >= cols) throw std::out_of_range("Index out of bounds");
    return data[r * cols + c];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimension mismatch for addition");
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] = data[i] + other.data[i];
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