
#include "gtest/gtest.h"
#include "../src/Network.h"
#include <vector>

using neurons::Network;

TEST(NetworkUtils, shouldReturnTheVectorOuputCorresponding) {
  Network network({1, 1, 10});
  EXPECT_EQ(std::vector<double>({ 0, 0, 0, 0, 0, -1, 0, 0, 0, 0 }), network.outputFor(5));
  EXPECT_EQ(std::vector<double>({ 0, -1, 0, 0, 0, 0, 0, 0, 0, 0 }), network.outputFor(1));
  EXPECT_EQ(std::vector<double>({ 0, 0, 0, 0, -1, 0, 0, 0, 0, 0 }), network.outputFor(4));
  EXPECT_EQ(std::vector<double>({ 0, -1, 0, 0, 0, 0, 0, 0, 0, 0 }), network.outputFor(1));
  EXPECT_EQ(std::vector<double>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 }), network.outputFor(9));
  EXPECT_EQ(std::vector<double>({ 0, 0, -1, 0, 0, 0, 0, 0, 0, 0 }), network.outputFor(2));
}

