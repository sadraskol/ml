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
using neurons::Cost;
using neurons::MnistData;

int main() {
  MnistData training_data(0, 50000);
  MnistData test_data(50000, 60000);
  Network network({ 784, 100, 10 }, Cost::newCrossEntropy());
  network.SGD(training_data, 40, 10, 0.5, test_data);
}
