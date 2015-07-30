/*
 * Matrix.h
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>

class Matrix {
public:
	Matrix(const double filler);
	virtual ~Matrix();
    const std::string toString();
};

#endif /* MATRIX_H_ */
