/*
 * MnistParser_test.cc
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "gtest/gtest.h"
#include "../src/MnistParser.h"
#include <vector>
#include <exception>

using neurons::MnistLabelParser;
using neurons::MnistImageParser;
using neurons::MnistData;
using neurons::Matrix;

TEST(MnistLabelParser, shouldReturnTheFirstNumbersCorrectly) {
  MnistLabelParser parser("data/train-labels-idx1-ubyte");
  ASSERT_EQ(std::vector<double>({ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }), parser.getLabel(0).getData());
  ASSERT_EQ(std::vector<double>({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }), parser.getLabel(1).getData());
  ASSERT_EQ(std::vector<double>({ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }), parser.getLabel(2).getData());
  ASSERT_EQ(std::vector<double>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }), parser.getLabel(3).getData());
  ASSERT_EQ(std::vector<double>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }), parser.getLabel(4).getData());
  ASSERT_EQ(std::vector<double>({ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }), parser.getLabel(5).getData());
}

TEST(MnistLabelParser, shouldNotPermitReadOnNonExistingIndex) {
  MnistLabelParser parser("data/train-labels-idx1-ubyte");
  EXPECT_THROW({ parser.getLabel(-1); } ,std::exception);
  parser.getLabel(60000);
  EXPECT_THROW({ parser.getLabel(60001); }, std::exception);
}

TEST(MnistImageParser, shouldReturnTheNthImageVectorized) {
  MnistImageParser parser("data/train-images-idx3-ubyte");
  std::vector<double> image = parser.getImage(0).getData();
  std::ostringstream oss;
  for (std::size_t i = 7 * 28; i < 8 * 28; i++) {
    oss << image[i] << " ";
  }
  ASSERT_STREQ("0 0 0 0 0 0 0 0.192157 0.933333 0.992157 0.992157 0.992157 0.992157 0.992157 0.992157 0.992157 0.992157 0.984314 0.364706 0.321569 0.321569 0.219608 0.152941 0 0 0 0 0 ", oss.str().c_str());
}

TEST(MnistImageParser, shouldNotPermitReadOnNonExistingIndex) {
  MnistImageParser parser("data/train-images-idx3-ubyte");
  EXPECT_THROW({ parser.getImage(-1); } ,std::exception);
  parser.getImage(60000);
  EXPECT_THROW({ parser.getImage(60001); } ,std::exception);
}

TEST(MnistData, shouldContainsTheSampleAskedFor) {
  MnistData data(3, 50);
  ASSERT_EQ(std::vector<double>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }), data.getLabel(0).getData());
  MnistImageParser parser("data/train-images-idx3-ubyte");
  ASSERT_EQ(parser.getImage(3).getData(), data.getImage(0).getData());
  ASSERT_EQ(47, data.size());
}

TEST(MnistData, shouldConvertDataToVector) {
  MnistData data(3, 50);
  std::vector<std::pair<Matrix, Matrix>> vectorized = data.get();
  ASSERT_EQ(std::vector<double>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }), vectorized[0].first.getData());
}
