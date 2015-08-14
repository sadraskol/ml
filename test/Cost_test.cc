#include "gtest/gtest.h"
#include "../src/Cost.h"

using namespace neurons;

TEST(QuadraticCost, normalCases) {
  const Cost* const cost = Cost::newQuadratic();
  const Matrix y = Matrix::create(1, 2, std::vector<double> { -1, 0 });
  const Matrix a = Matrix::create(1, 2, std::vector<double> { 3, -4 });
  EXPECT_NEAR(16, cost->cost(a, y), 0.000001);
  const Matrix z = Matrix::create(1, 2, std::vector<double> { 0, 0 });
  const Matrix delta = cost->delta(z, a, y);
  EXPECT_NEAR(1, delta.getData()[0], 0.000001);
  EXPECT_NEAR(-1, delta.getData()[1], 0.000001);
}

TEST(CrossEntropyCost, normalCases) {
  const Cost* const cost = Cost::newCrossEntropy();
  const Matrix y = Matrix::create(1, 2, std::vector<double> { 1, 1 });
  const Matrix a = Matrix::create(1, 2, std::vector<double> { 0.5, 0.5 });
  EXPECT_NEAR(1.386294, cost->cost(a, y), 0.000001);
  const Matrix z = Matrix::create(1, 2, std::vector<double> { 0.12315, 0.565785 });
  const Matrix delta = cost->delta(z, a, y);
  EXPECT_NEAR(-0.5, delta.getData()[0], 0.000001);
  EXPECT_NEAR(-0.5, delta.getData()[1], 0.000001);
}

TEST(CrossEntropyCost, limitCase) {
  const Cost* const cost = Cost::newCrossEntropy();
  const Matrix y = Matrix::create(1, 2, std::vector<double> { 1, 1 });
  const Matrix a = Matrix::create(1, 2, std::vector<double> { 0, 1 });
  EXPECT_NEAR(0, cost->cost(a, y), 0.000001);
}
