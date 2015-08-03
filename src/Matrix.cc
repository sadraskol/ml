/*
 * Matrix.cpp
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "Matrix.h"
#include <cmath>
#include <sstream>

using neurons::Matrix;

Matrix::Matrix(const std::size_t& rows, const std::size_t& cols,
		const std::vector<double>& _data) {
	if (_data.size() < rows * cols) {
		throw std::invalid_argument("Data contains not enough data");
	}
	this->rows = rows;
	this->cols = cols;
	this->data = _data;
}

Matrix::Matrix(const std::size_t& rows, const std::size_t& cols, const std::function<double()>& filler) {
	this->rows = rows;
	this->cols = cols;
	this->data = std::vector<double>(rows * cols);
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			this->data[i * cols + j] = filler();
		}
	}
}

const std::string Matrix::toString() const {
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

const std::string Matrix::toPgm() const {
    std::ostringstream os;
	os << "P2\n" << this->rows << " " <<  this->cols << "\n255\n";
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			os << std::to_string((int) get(i, j)) << " ";
		}
        os << "\n";
	}
	return os.str();
}

const Matrix Matrix::operator*(const double& alpha) const {
    return this->transform([alpha](const double& input) {
        return alpha * input;
    });
}

const Matrix Matrix::product(const Matrix& right) const {
    if (this->cols != right.rows) {
        throw std::invalid_argument("size should match");
    }
    Matrix product(rows, right.cols, std::vector<double>(this->rows * right.cols));
    for (std::size_t i = 0; i < this->rows; i++) {
        for (std::size_t j = 0; j < right.cols; j++) {
            double accumulator = 0;
            for (std::size_t k = 0; k < this->cols; k++) {
                accumulator += get(i, k) * right.get(k, j);
            }
            product.set(i, j, accumulator);
        }
    }
    return product;
}

double Matrix::get(const std::size_t& x, const std::size_t& y) const {
    if ((int) x < 0 || x >= this->rows || (int) y < 0 || y >= this->cols) {
        throw std::invalid_argument("Out of Bound get");
    }
    return this->data[x * this->cols + y];
}

const Matrix Matrix::operator+(const Matrix& other) const {
    std::vector<double> new_data(this->rows * this->cols);
    for (std::size_t i = 0; i < new_data.size(); i++) {
        new_data[i] = this->data[i] + other.data[i];
    }
    return Matrix(this->rows, this->cols, new_data);
}

const Matrix Matrix::operator-() const {
    return this->transform([](const double &input) {
        return -input;
    });
}

const Matrix Matrix::operator-(const Matrix& other) const {
    std::vector<double> new_data(this->rows * this->cols);
    for (std::size_t i = 0; i < new_data.size(); i++) {
        new_data[i] = this->data[i] - other.data[i];
    }
    return Matrix(this->rows, this->cols, new_data);
}

const Matrix Matrix::operator/(const double& divisor) const {
    if (divisor == 0) {
        throw std::invalid_argument("can not divid by zero");
    }
    return this->transform([divisor](const double &input) {
        return input / divisor;
    });
}

void Matrix::set(const std::size_t& i, const std::size_t& j, const double& value) {
	this->data[i * this->cols + j] = value;
}

const Matrix Matrix::toExp() const {
    return this->transform([](const double& input) {
        return exp(input);
    });
}

const Matrix Matrix::sigmoid() const {
    return 1 / ( 1 + (-(*this)).toExp());
}

const Matrix Matrix::transform(const std::function<double(double)>& transformer) const {
    std::vector<double> new_data(this->rows * this->cols);
    for (std::size_t i = 0; i < this->rows; i++) {
        for (std::size_t j = 0; j < this->cols; j++) {
            new_data[i * this->cols + j] = transformer(this->get(i, j));
        }
    }
    return Matrix(this->rows, this->cols, new_data);
}
