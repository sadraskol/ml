
#include <cmath>
#include "Cost.h"
#include "gtest/gtest.h"

namespace neurons {

  const Cost* Cost::newQuadratic() {
    return new QuadraticCost();
  }

  const Cost* Cost::newCrossEntropy() {
    return new CrossEntropyCost();
  }

  double QuadraticCost::cost(const Matrix& a, const Matrix& y) const {
    std::vector<double> data = (a - y).getData();
    double accumulator = 0;
    for (std::size_t i = 0; i < data.size(); ++i) {
      accumulator += data[i] * data[i];
    }
    return accumulator / 2;
  }

  const Matrix QuadraticCost::delta(const Matrix& z, const Matrix& a, const Matrix& y) const {
    return (a - y) * z.sigmoid_prime();
  }

  double CrossEntropyCost::cost(const Matrix& a, const Matrix& y) const {
    std::vector<double> a_data = a.getData();
    std::vector<double> y_data = y.getData();
    double accumulator = 0;
    for (std::size_t i = 0; i < a_data.size(); ++i) {
      if (a_data[i] == 1 || a_data[i] == 0) {
        return 0;
      }
      accumulator += - y_data[i] * log(a_data[i]) - (1 - y_data[i]) * log(1 - a_data[i]);
    }
    return accumulator;
  }

  const Matrix CrossEntropyCost::delta(const Matrix& z, const Matrix& a, const Matrix& y) const {
    return a - y;
  }

} // namespace neurons

