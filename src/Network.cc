/*
 * Network.cc
 *
 *  Created on: 1 août 2015
 *      Author: thomas
 */

#include "Network.h"
#include "stdio.h"

using neurons::Matrix;
using neurons::Network;
using neurons::MnistData;

Network::Network(const std::vector<std::size_t>& sizes) {
    this->num_layers = sizes.size();
    this->sizes = sizes;
    this->biases = std::vector<Matrix>(0);
    this->weights = std::vector<Matrix>(0);
    const std::function<double()> gaussian_random_generator = []() {
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    };
    for (std::size_t size = 1; size < sizes.size(); size++) {
        Matrix element(sizes[size], 1, gaussian_random_generator);
        this->biases.push_back(element);
    }
    for (std::size_t left = 0; left < sizes.size() - 1; left++) {
        const std::size_t right = left + 1;
        Matrix element(sizes[left], sizes[right], gaussian_random_generator);
        this->weights.push_back(element);
    }
}

const Matrix Network::feed_forward(const Matrix& input) const {
    //for b, w in zip(self.biases, self.weights):
    //   a = sigmoid_vec(np.dot(w, a)+b)
    //   return a
    Matrix result = input;
    for (std::size_t index; index < this->weights.size(); index++) {
        result = (this->weights[index].product(input) + this->biases[index]).sigmoid();
    }
    return result;
}

void Network::SGD(const MnistData& training_data, const std::size_t& epochs, const std::size_t& mini_batch_size, const double eta, const MnistData& test_data) {
    const std::size_t n = training_data.size();
    for (std::size_t j = 0; j < epochs; j++) {
        std::vector<std::pair<int, std::vector<unsigned char>>> randomized_data = training_data.randomize();
        std::vector<std::vector<std::pair<int, std::vector<unsigned char>>>> mini_batches;
        for (std::size_t k = 0; k < n; k += mini_batch_size) {
            std::vector<std::pair<int, std::vector<unsigned char>>> mini_batch;
            for (std::size_t l = 0; l < mini_batch_size; l++) {
                mini_batch.push_back(randomized_data[k + l]);
            }
            mini_batches.push_back(mini_batch);
        }
        for (auto mini_batch: mini_batches) {
            this->update_mini_batch(mini_batch, eta);
        }
        printf("Epoch %lu: %d / %lu\n", j, this->evaluate(test_data), test_data.size());
    }
}

void Network::update_mini_batch(const std::vector<std::pair<int, std::vector<unsigned char>>>& mini_batch, const double eta) {
    std::vector<Matrix> nabla_b, nabla_w;
    for (auto bias: this->biases) {
        nabla_b.push_back(neurons::zeros(bias.getRows(), bias.getCols()));
    }
    for (auto weight: this->weights) {
        nabla_b.push_back(neurons::zeros(weight.getRows(), weight.getCols()));
    }
    for (auto batch: mini_batch) {
        std::pair<std::vector<Matrix>, std::vector<Matrix>> delta_nablas = this->backprop(batch.first, batch.second);
        std::vector<Matrix> delta_nabla_b = delta_nablas.first;
        std::vector<Matrix> delta_nabla_w = delta_nablas.second;
        for (std::size_t i = 0; i < nabla_b.size(); i++) {
            nabla_b[i] = nabla_b[i] + delta_nabla_b[i];
        }
        for (std::size_t i = 0; i < nabla_w.size(); i++) {
            nabla_w[i] = nabla_w[i] + delta_nabla_w[i];
        }
    }
    for (std::size_t i = 0; i < this->weights.size(); i++) {
        this->weights[i] = this->weights[i] - (eta / mini_batch.size()) * nabla_w[i];
    }
    for (std::size_t i = 0; i < this->biases.size(); i++) {
        this->biases[i] = this->biases[i] - (eta / mini_batch.size()) * nabla_b[i];
    }
}

const std::pair<std::vector<Matrix>, std::vector<Matrix>> Network::backprop(const int label, const std::vector<unsigned char>& image) const {
    std::vector<Matrix> nabla_b, nabla_w;
    for (auto bias: this->biases) {
        nabla_b.push_back(neurons::zeros(bias.getRows(), bias.getCols()));
    }
    for (auto weight: this->weights) {
        nabla_w.push_back(neurons::zeros(weight.getRows(), weight.getCols()));
    }

    Matrix activation(1, image.size(), std::vector<double>(image.begin(), image.end()));
    std::vector<Matrix> activations(1, activation);
    std::vector<Matrix> zs(0);
    for (std::size_t i = 0; i < this->weights.size(); i++) {
        Matrix z = activation.product(this->weights[i]) + this->biases[i].transpose();
        zs.push_back(z);
        activation = z.sigmoid();
        activations.push_back(activation);
    }

    // FIXME what does this delta return ?
    Matrix delta = ((-label) + activations[activations.size() - 1]) * zs[zs.size() - 1].sigmoid_prime();
    nabla_b[nabla_b.size() - 1] = delta;
    nabla_w[nabla_w.size() - 1] = activations[activations.size() - 2].transpose().product(delta);
    for (std::size_t l = 2; l < this->num_layers; l++) {
        Matrix z = zs[zs.size() - l];
        Matrix spv = z.sigmoid_prime();
        // FIXME delta should be some (30 1) matrix not a (30 10) at first iteration
        Matrix delta = (this->weights[this->weights.size() + 1 - l].transpose().product(delta)) * spv;
        nabla_b[nabla_b.size() - l] = delta;
        nabla_w[nabla_w.size() - l] = activations[activations.size() - l - 1].transpose().product(delta);
    }
    return std::make_pair(nabla_b, nabla_w);
}
