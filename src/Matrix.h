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
      Matrix() {}

      explicit Matrix(const std::size_t& rows, const std::size_t& cols, const std::function<double()>& filler);

      virtual ~Matrix() {}

      const Matrix product(const Matrix& right) const;
      const Matrix toExp() const;
      const Matrix sigmoid() const;
      const Matrix sigmoid_prime() const;
      const Matrix transpose() const;

      std::size_t getRows() const { return this->rows; }
      std::size_t getCols() const { return this->cols; }

      double get(const std::size_t& x, const std::size_t& y) const;

      const Matrix operator+(const Matrix& other) const;
      Matrix& operator+=(const Matrix& other);
      friend const Matrix operator+(const double& alpha, const Matrix& right) {
        return right.transform([alpha](const double& input) {
            return input + alpha;
            });
      }
      const Matrix operator-() const;
      const Matrix operator-(const Matrix& other) const;
      friend const Matrix operator-(const double& alpha, const Matrix& right) {
        return right.transform([alpha](const double& input) {
            return alpha - input;
            });
      }
      const Matrix operator*(const double& alpha) const;
      const Matrix operator*(const Matrix& other) const;
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

      std::size_t argmax() const;
      const std::string toString() const;
      const std::string toPgm() const;
      const std::vector<double> getData() const { return this->data; }

      static const Matrix create(const std::size_t& rows, const std::size_t& cols,
          const std::vector<double>& data);
      static const Matrix zeros(const std::size_t& rows, const std::size_t& cols);

    private:
      explicit Matrix(const std::size_t& _rows, const std::size_t& _cols, const std::vector<double>& _data);
      void set(const std::size_t& i, const std::size_t& j, const double& value);
      const Matrix transform(const std::function<double(double)>& transformer) const;
      std::size_t rows;
      std::size_t cols;
      std::vector<double> data;
  };
} // namespace neurons

#endif /* MATRIX_H_ */
