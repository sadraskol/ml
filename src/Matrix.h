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

namespace neurons {

    class Matrix {
    public:
        explicit Matrix(const std::size_t& rows, const std::size_t& cols, const std::vector<double>& _data);

        explicit Matrix(const std::size_t& rows, const std::size_t& cols, const std::function<double()>& filler);

        virtual ~Matrix() {
            this->data.clear();
        }

        const Matrix product(const Matrix& right) const;
        const Matrix toExp() const;
        const Matrix sigmoid() const;

        std::size_t getRows() const { return this->rows; }
        std::size_t getCols() const { return this->cols; }

        double get(const std::size_t& x, const std::size_t& y) const;

        const Matrix operator+(const Matrix& other) const;
        friend const Matrix operator+(const double& alpha, const Matrix& right) {
            return right.transform([alpha](const double& input) {
                return input + alpha;
            });
        }
        const Matrix operator-() const;
        const Matrix operator-(const Matrix& other) const;
        const Matrix operator*(const double& alpha) const;
        friend const Matrix operator*(const double& alpha, const Matrix& right) {
            return right.transform([alpha](const double& input) {
                return input * alpha;
            });
        }
        const Matrix operator/(const double& divisor) const;
        friend const Matrix operator/(const double& dividend, const Matrix& divisor) {
            return divisor.transform([dividend](const double& input) {
                return dividend / input;
            });
        }

        const std::string toString() const;
        const std::string toPgm() const;

    private:
        void set(const std::size_t& i, const std::size_t& j, const double& value);
        const Matrix transform(const std::function<double(double)>& transformer) const;
        std::size_t rows;
        std::size_t cols;
        std::vector<double> data;
    };

}

#endif /* MATRIX_H_ */

