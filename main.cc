/*
 * main.cpp
 *
 *  Created on: 30 juil. 2015
 *      Author: Thomas Bracher
 */
#include <iostream>
#include <fstream>
#include <vector>
#include "stdio.h"
#include "src/Network.h"
#include "src/MnistParser.h"

using neurons::Network;
using neurons::MnistData;

int main() {
    MnistData training_data(0, 50000);
    MnistData test_data(50000, 60000);
    Network network({ 784, 10 });
    network.SGD(training_data, 30, 10, 3.0, training_data);
}
