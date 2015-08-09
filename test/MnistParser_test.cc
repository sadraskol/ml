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

TEST(MnistLabelParser, shouldReturnTheFirstNumbersCorrectly) {
    MnistLabelParser parser("data/train-labels-idx1-ubyte");
    ASSERT_EQ(5, parser.getLabel(0));
    ASSERT_EQ(0, parser.getLabel(1));
    ASSERT_EQ(4, parser.getLabel(2));
    ASSERT_EQ(1, parser.getLabel(3));
    ASSERT_EQ(9, parser.getLabel(4));
    ASSERT_EQ(2, parser.getLabel(5));
}

TEST(MnistLabelParser, shouldNotPermitReadOnNonExistingIndex) {
    MnistLabelParser parser("data/train-labels-idx1-ubyte");
    try {
        parser.getLabel(-1);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
    parser.getLabel(60000);
    try {
        parser.getLabel(60001);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
}

TEST(MnistImageParser, shouldReturnTheNthImageVectorized) {
    MnistImageParser parser("data/train-images-idx3-ubyte");
    std::vector<unsigned char> image = parser.getImage(0);
    std::ostringstream oss;
    for (std::size_t i = 7 * 28; i < 8 * 28; i++) {
        oss << (int) image[i] << " ";
    }
    ASSERT_STREQ("0 0 0 0 0 0 0 49 238 253 253 253 253 253 253 253 253 251 93 82 82 56 39 0 0 0 0 0 ", oss.str().c_str());
}

TEST(MnistImageParser, shouldNotPermitReadOnNonExistingIndex) {
    MnistImageParser parser("data/train-images-idx3-ubyte");
    try {
        parser.getImage(-1);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
    parser.getImage(60000);
    try {
        parser.getImage(60001);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
}

TEST(MnistData, shouldContainsTheSampleAskedFor) {
    MnistData data(3, 50);
    ASSERT_EQ(1, data.getLabel(0));
    MnistImageParser parser("data/train-images-idx3-ubyte");
    ASSERT_EQ(parser.getImage(3), data.getImage(0));
    ASSERT_EQ(47, data.size());
}

