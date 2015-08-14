
#include "gtest/gtest.h"
#include "../src/Network.h"

using namespace neurons;

TEST(NetworkTest, ShouldLearnDeterministiclyWithOneNeuron) {
  Matrix weigth = Matrix::create(1, 1, std::vector<double>{ 0.6 });
  Matrix bias = Matrix::create(1, 1, std::vector<double>{ 0.9 });
  Network network(std::vector<Matrix>({ weigth }), std::vector<Matrix>({bias}));
  Matrix output = network.feed_forward(Matrix::create(1, 1, std::vector<double> { 1 }));
  EXPECT_NEAR(0.817574, output.getData()[0], 0.000001);
}
