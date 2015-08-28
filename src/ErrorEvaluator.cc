
#include <numeric>
#include <cmath>
#include <algorithm>

#include "ErrorEvaluator.h"

using neurons::ErrorEvaluator;

const std::vector<double> ErrorEvaluator::evaluate(const std::vector<double>& expected,
    const std::vector<double>& actual) const {

  std::vector<double> result(expected.size());
  double sumActual = std::accumulate(actual.begin() + 1, actual.end(), actual[0],
      [](double left, double right) { return left + right; });
  for (int i = 0; i < expected.size(); ++i) {
    result[i] = actual[i] / sumActual;
  }
  return result;
}

std::size_t argmax(const std::vector<double>& v) {
  return std::distance(v.begin(), std::max_element(v.begin(), v.end(),
        [](const double& a, const double& b) { return std::abs(a) < std::abs(b); }));
}

bool ErrorEvaluator::isSuccess(const std::vector<double>& expected,
    const std::vector<double>& actual) const {
  return argmax(expected) == argmax(actual);
}

