/*
 * Network.cc
 *
 *  Created on: 1 août 2015
 *      Author: thomas
 */

#include "Network.h"

using neurons::Matrix;
using neurons::Network;

Network::Network(const std::vector<std::size_t>& sizes) {
    this->num_layers = sizes.size();
    this->sizes = sizes;
    this->biases = std::vector<Matrix *>(0);
    this->weights = std::vector<Matrix *>(0);
    const std::function<double()> gaussian_random_generator = []() {
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    };
    for (std::size_t size = 1; size < sizes.size(); size++) {
        Matrix *element = new Matrix(sizes[size], 1, gaussian_random_generator);
        this->biases.push_back(element);
    }
    for (std::size_t left = 0; left < sizes.size() - 1; left++) {
        const std::size_t right = left + 1;
        Matrix *element = new Matrix(sizes[left], sizes[right], gaussian_random_generator);
        this->weights.push_back(element);
    }
}

const Matrix Network::feed_forward(const Matrix& input) const {
    //for b, w in zip(self.biases, self.weights):
    //   a = sigmoid_vec(np.dot(w, a)+b)
    //   return a
    Matrix result = input;
    for (std::size_t index; index < this->weights.size(); index++) {
        result = (this->weights[index]->product(input) + (*this->biases[index])).sigmoid();
    }
    return result;
}

