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
        Matrix<2, 3> matrix(std::vector<double> { 0, 0, 0, 0, 0 });
        FAIL() << "matrix should not build with unsufficient data";
    } catch (std::exception& e) {
        SUCCEED() << "matrix throwed an expected error";
    }
}

TEST(MatrixTest, ToStringWhenInitializing) {
	Matrix<2, 3> matrix(std::vector<double> { 0, 0, 0, 0, 0, 0 });
	EXPECT_STREQ("[ 0 0 0\n  0 0 0 ]", matrix.toString().c_str());
}

TEST(MatrixTest, ScalarMultiplication) {
    const Matrix<2, 2> matrix_a(std::vector<double> { 1, 1, 2, 3 });
	EXPECT_STREQ("[ 1 1\n  2 3 ]", matrix_a.toString().c_str());
    const Matrix<2, 2> matrix_b = matrix_a.multiply(4);
	EXPECT_STREQ("[ 4 4\n  8 12 ]", matrix_b.toString().c_str());
}

TEST(MatrixTest, MatrixShouldBeOkForProduct) {
    const Matrix<2, 2> matrix_a(std::vector<double> { 1, 1, 2, 3 });
    const Matrix<3, 1> matrix_b(std::vector<double> { 1, 1, 2 });
    try {
        matrix_a.product(matrix_b);
        FAIL() << "matrix size should not be legal";
    } catch (std::exception& e) {
        SUCCEED() << "throwed error";
    }
}

TEST(MatrixTest, RespectProductProperties) {
    const Matrix<2, 2> matrix_a(std::vector<double> { 1, 1, 2, 3 });
    const Matrix<2, 1> matrix_b(std::vector<double> { 1, 1 });
    EXPECT_STREQ("[ 2\n  5 ]", matrix_a.product(matrix_b).toString().c_str());

    const Matrix<1, 3> matrix_c(std::vector<double> { 1, 2, 3 });
    const Matrix<3, 1> matrix_d(std::vector<double> { -6, -1, 4 });
    EXPECT_STREQ("[ 4 ]", matrix_c.product(matrix_d).toString().c_str());
    EXPECT_STREQ("[ -6 -12 -18\n  -1 -2 -3\n  4 8 12 ]", matrix_d.product(matrix_c).toString().c_str());
}

TEST(MatrixTest, AddMatrixTogether) {
    const Matrix<2, 3> matrix_a(std::vector<double> { 1, 3, 1, 5, 1, 7 });
    const Matrix<2, 3> matrix_b(std::vector<double> { 1, 1, 0, 1, 1, -1 });
    EXPECT_STREQ("[ 2 4 1\n  6 2 6 ]", (matrix_a + matrix_b).toString().c_str());
}
