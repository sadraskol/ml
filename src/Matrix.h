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
#include <functional>

class Matrix {
public:
	explicit Matrix(const std::size_t& rows, const std::size_t& cols, const std::vector<double>& _data);

    explicit Matrix(const std::size_t& rows, const std::size_t& cols, const std::function<double(std::size_t, std::size_t)>& filler);

	virtual ~Matrix() {}

    const std::string toString() const;

    const Matrix multiply(const double& alpha) const;

    const Matrix product(const Matrix& right) const;

    double get(const std::size_t& x, const std::size_t& y) const;

    const Matrix operator+(const Matrix& other) const;

private:
    void set(const std::size_t& i, const std::size_t& j, const double& value);
    std::size_t rows;
    std::size_t cols;
    std::vector<double> data;
};

#endif /* MATRIX_H_ */
