/*
 * Matrix_test.cpp
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "gtest/gtest.h"
#include "../src/Matrix.h"

TEST(MatrixTest, ShouldNotAcceptUnsufficientData) {
    try {
    	const Matrix matrix(2, 3, std::vector<double> { 0, 0, 0, 0, 0 });
        FAIL() << "matrix should not build with unsufficient data";
    } catch (std::exception& e) {
        SUCCEED() << "matrix throwed an expected error";
    }
}

TEST(MatrixTest, ToStringWhenInitializing) {
	Matrix matrix(2, 3, std::vector<double> { 0, 0, 0, 0, 0, 0 });
	EXPECT_STREQ("[ 0 0 0\n  0 0 0 ]", matrix.toString().c_str());
}

TEST(MatrixTest, ScalarMultiplication) {
    const Matrix matrix_a(2, 2, std::vector<double> { 1, 1, 2, 3 });
	EXPECT_STREQ("[ 1 1\n  2 3 ]", matrix_a.toString().c_str());
	EXPECT_STREQ("[ 4 4\n  8 12 ]", matrix_a.multiply(4).toString().c_str());
    const Matrix matrix_b(4, 2, std::vector<double> { 1, 2, 3, -1, -2, -4, 2, 2 });
    EXPECT_STREQ("[ -1 -2\n  -3 1\n  2 4\n  -2 -2 ]", matrix_b.multiply(-1).toString().c_str());
}

TEST(MatrixTest, MatrixShouldBeOkForProduct) {
    const Matrix matrix_a(2, 2, std::vector<double> { 1, 1, 2, 3 });
    const Matrix matrix_b(3, 1, std::vector<double> { 1, 1, 2 });
    try {
        matrix_a.product(matrix_b);
        FAIL() << "matrix size should not be legal";
    } catch (std::exception& e) {
        SUCCEED() << "throwed error";
    }
}

TEST(MatrixTest, RespectProductProperties) {
    const Matrix matrix_a(2, 2, std::vector<double> { 1, 1, 2, 3 });
    const Matrix matrix_b(2, 1, std::vector<double> { 1, 1 });
    EXPECT_STREQ("[ 2\n  5 ]", matrix_a.product(matrix_b).toString().c_str());

    const Matrix matrix_c(1, 3, std::vector<double> { 1, 2, 3 });
    const Matrix matrix_d(3, 1, std::vector<double> { -6, -1, 4 });
    EXPECT_STREQ("[ 4 ]", matrix_c.product(matrix_d).toString().c_str());
    EXPECT_STREQ("[ -6 -12 -18\n  -1 -2 -3\n  4 8 12 ]", matrix_d.product(matrix_c).toString().c_str());
}

TEST(MatrixTest, AddMatrixTogether) {
    const Matrix matrix_a(2, 3, std::vector<double> { 1, 3, 1, 5, 1, 7 });
    const Matrix matrix_b(2, 3, std::vector<double> { 1, 1, 0, 1, 1, -1 });
    EXPECT_STREQ("[ 2 4 1\n  6 2 6 ]", (matrix_a + matrix_b).toString().c_str());
}

TEST(MatrixTest, FillUpTheMatrix) {
    const Matrix matrix_a(2, 3, [](const std::size_t& i, const std::size_t& j) { return 1; });
    EXPECT_STREQ("[ 1 1 1\n  1 1 1 ]", matrix_a.toString().c_str());
}
