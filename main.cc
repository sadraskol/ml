/*
 * main.cpp
 *
 *  Created on: 30 juil. 2015
 *      Author: Thomas Bracher
 */
#include <iostream>
#include <fstream>
#include <vector>
#include "src/Matrix.h"

using neurons::Matrix;

int main() {
    std::ifstream images("data/train-images-idx3-ubyte", std::ifstream::binary);
    images.seekg(16);
    // parsing part
    std::vector<double> data(784);
    for (std::size_t i = 0; i < 28; i++) {
        for(std::size_t j = 0; j < 28; j++) {
            data[i * 28 + j] = images.get();
        }
    }

    // output as and image part
    Matrix matrix(28, 28, data);
    std::cout << matrix.toPgm();
    return 0;
}

