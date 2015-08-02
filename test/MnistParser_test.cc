/*
 * MnistParser_test.cc
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "gtest/gtest.h"
#include "../src/MnistParser.h"

using neurons::MnistLabelParser;

TEST(MnistParser, shouldReturnTheFirstNumbersCorrectly) {
    MnistLabelParser parser("data/train-labels-idx1-ubyte");
    ASSERT_EQ(5, parser.getLabel(0));
    ASSERT_EQ(0, parser.getLabel(1));
    ASSERT_EQ(4, parser.getLabel(2));
    ASSERT_EQ(1, parser.getLabel(3));
    ASSERT_EQ(9, parser.getLabel(4));
    ASSERT_EQ(2, parser.getLabel(5));
}

