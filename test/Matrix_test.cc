/*
 * Matrix_test.cpp
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "gtest/gtest.h"
#include "../src/Matrix.h"

TEST(MatrixTest, ToStringWhenInitializing) {
	Matrix matrix(0);
	EXPECT_STREQ("super", matrix.toString().c_str());
}
