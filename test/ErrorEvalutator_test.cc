
#include "gtest/gtest.h"
#include "../src/ErrorEvaluator.h"
#include <vector>

using neurons::ErrorEvaluator;

TEST(ErrorEvaluator, ShouldReturn100WhenSure) {
  std::vector<double> expected({ 1, 0 });
  std::vector<double> actual({ 1, 0 });
  ErrorEvaluator evaluator;
  ASSERT_EQ(std::vector<double>({ 1, 0 }), evaluator.evaluate(expected, actual));
  ASSERT_TRUE(evaluator.isSuccess(expected, actual));
}

TEST(ErrorEvaluator, ShouldReturn0WhenFailure) {
  std::vector<double> expected({ 1, 0 });
  std::vector<double> actual({ 0, 1 });
  ErrorEvaluator evaluator;
  ASSERT_EQ(std::vector<double>({ 0, 1 }), evaluator.evaluate(expected, actual));
  ASSERT_FALSE(evaluator.isSuccess(expected, actual));
}

TEST(ErrorEvaluator, ShouldReturnUncertaintyScore) {
  std::vector<double> expected({ 1, 0 });
  std::vector<double> actual({ 0.3, 0.9 });
  ErrorEvaluator evaluator;
  ASSERT_EQ(std::vector<double>({ 0.25, 0.75 }), evaluator.evaluate(expected, actual));
  ASSERT_FALSE(evaluator.isSuccess(expected, actual));
}
