/*
 * Matrix.h
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

template<std::size_t rows, std::size_t cols>
class Matrix {
public:
	Matrix(const std::vector<double>& _data) {
        if (_data.size() < rows * cols) {
            throw std::invalid_argument("vector<double> should be exactly" + rows * cols);
        }
        this->data = _data;
    }

	virtual ~Matrix() {}

    const std::string toString() const {
        std::string result("[");
        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < cols; j++) {
                result += " ";
                result += std::to_string((int) get(i, j));
            }
            if (i < rows - 1) {
                result += "\n ";
            }
        }
        result += " ]";
        return result;
    }

    const Matrix<rows, cols> multiply(const double alpha) const {
        std::vector<double> new_data(rows * cols);
        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < cols; j++) {
                new_data[i * rows + j] = alpha * get(i, j);
            }
        }
        return Matrix<rows, cols>(new_data);
    }

    template<std::size_t other_rows, std::size_t other_cols>
    const Matrix<rows, other_cols> product(const Matrix<other_rows, other_cols>& right) const {
        if (cols != other_rows) {
            throw std::invalid_argument("size should match");
        }
        std::vector<double> new_data(rows * other_cols);
        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < other_cols; j++) {
                double accumulator = 0;
                for (std::size_t k = 0; k < cols; k++) {
                    accumulator += get(i, k) * right.get(k, j);
                }
                new_data[i * other_cols + j] = accumulator;
            }
        }
        return Matrix<rows, other_cols>(new_data);
    }

    double get(const std::size_t x, const std::size_t y) const {
        return this->data[x * cols + y];
    }

    const Matrix<rows, cols> operator+(const Matrix<rows, cols> &other) const {
        std::vector<double> new_data(rows * cols);
        for (std::size_t i = 0; i < new_data.size(); i++) {
            new_data[i] = this->data[i] + other.data[i];
        }
        return Matrix<rows, cols>(new_data);
    }

private:
    std::vector<double> data;
};

#endif /* MATRIX_H_ */
