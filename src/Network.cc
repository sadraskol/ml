/*
 * Network.cc
 *
 *  Created on: 1 août 2015
 *      Author: thomas
 */

#include "Network.h"
#include "stdio.h"
#include <ctime>

using neurons::Matrix;
using neurons::Network;
using neurons::MnistData;

static double gaussian_random_generator() {
  std::default_random_engine generator(std::clock());
  static std::normal_distribution<double> distribution(0.0, 1.0);
  return distribution(generator);
}

Network::Network(const std::vector<std::size_t>& sizes) {
  this->num_layers = sizes.size();
  this->sizes = sizes;
  this->biases = std::vector<Matrix>(sizes.size() - 1);
  this->weights = std::vector<Matrix>(sizes.size() - 1);
  for (std::size_t size = 1; size < sizes.size(); size++) {
    const std::size_t left = size - 1;
    this->weights[left] = Matrix(sizes[left], sizes[size], gaussian_random_generator);
    this->biases[left] = Matrix(sizes[size], 1, gaussian_random_generator);
  }
}

const Matrix Network::feed_forward(const Matrix& input) const {
  Matrix output = input;
  for (std::size_t index = 0; index < this->weights.size(); index++) {
    output = (this->weights[index].transpose().product(output) + this->biases[index]).sigmoid();
  }
  return output;
}

void Network::SGD(const MnistData& training_data, const std::size_t& epochs, const std::size_t& mini_batch_size, const double eta, const MnistData& test_data) {
  const std::size_t n = training_data.size();
  for (std::size_t j = 0; j < epochs; j++) {
    std::clock_t start_epoch = std::clock();
    std::vector<std::pair<Matrix, Matrix>> randomized_data = training_data.randomize();
    std::vector<std::vector<std::pair<Matrix, Matrix>>> mini_batches;
    for (std::size_t k = 0; k < n; k += mini_batch_size) {
      std::vector<std::pair<Matrix, Matrix>> mini_batch;
      for (std::size_t l = 0; l < mini_batch_size; l++) {
        mini_batch.push_back(randomized_data[k + l]);
      }
      mini_batches.push_back(mini_batch);
    }
    for (std::size_t i = 0; i < mini_batches.size(); i++) {
      this->update_mini_batch(mini_batches[i], eta);
    }
    int evaluation = this->evaluate(test_data);
    printf("Epoch %lu: %d / %lu (%li)\n", j, evaluation, test_data.size(), std::clock() - start_epoch);
  }
}

void Network::update_mini_batch(const std::vector<std::pair<Matrix, Matrix>>& mini_batch, const double eta) {
  std::vector<Matrix> nabla_b(0), nabla_w(0);
  for (auto bias: this->biases) {
    nabla_b.push_back(Matrix::zeros(bias.getRows(), bias.getCols()));
  }
  for (auto weight: this->weights) {
    nabla_w.push_back(Matrix::zeros(weight.getRows(), weight.getCols()));
  }
  for (auto batch: mini_batch) {
    std::pair<std::vector<Matrix>, std::vector<Matrix>> delta_nablas = this->backprop(batch.first, batch.second);
    std::vector<Matrix> delta_nabla_b = delta_nablas.first;
    std::vector<Matrix> delta_nabla_w = delta_nablas.second;
    for (std::size_t i = 0; i < nabla_b.size(); i++) {
      nabla_b[i] += delta_nabla_b[i];
    }
    for (std::size_t i = 0; i < nabla_w.size(); i++) {
      nabla_w[i] += delta_nabla_w[i];
    }
  }
  for (std::size_t i = 0; i < this->weights.size(); i++) {
    this->weights[i] += (-eta / mini_batch.size()) * nabla_w[i];
  }
  for (std::size_t i = 0; i < this->biases.size(); i++) {
    this->biases[i] += (-eta / mini_batch.size()) * nabla_b[i];
  }
}

const std::pair<std::vector<Matrix>, std::vector<Matrix>> Network::backprop(const Matrix& label, const Matrix& image) const {
  std::vector<Matrix> nabla_b, nabla_w;
  for (auto bias: this->biases) {
    nabla_b.push_back(Matrix::zeros(bias.getRows(), bias.getCols()));
  }
  for (auto weight: this->weights) {
    nabla_w.push_back(Matrix::zeros(weight.getRows(), weight.getCols()));
  }

  Matrix activation = image;
  std::vector<Matrix> activations(1, activation);
  std::vector<Matrix> zs(0);
  for (std::size_t i = 0; i < this->weights.size(); i++) {
    Matrix z = this->weights[i].transpose().product(activation) + this->biases[i];
    zs.push_back(z);
    activation = z.sigmoid();
    activations.push_back(activation);
  }

  Matrix delta = this->cost_derivative(activations[activations.size() - 1], label) \
                 * zs[zs.size() - 1].sigmoid_prime();
  nabla_b[nabla_b.size() - 1] = delta;
  nabla_w[nabla_w.size() - 1] = activations[activations.size() - 2].product(delta.transpose());
  for (std::size_t l = 2; l < this->num_layers; l++) {
    Matrix z = zs[zs.size() - l];
    Matrix spv = z.sigmoid_prime();
    delta = this->weights[this->weights.size() + 1 - l].product(delta) * spv;
    nabla_b[nabla_b.size() - l] = delta;
    nabla_w[nabla_w.size() - l] = activations[activations.size() - l - 1].product(delta.transpose());
  }
  return std::make_pair(nabla_b, nabla_w);
}

int Network::evaluate(const MnistData& data) const {
  std::vector<std::pair<Matrix, Matrix>> test_data = data.randomize();
  int total = 0;
  for (std::size_t i = 0; i < test_data.size(); i++) {
    const std::size_t expected = test_data[i].first.argmax();
    const std::size_t actual = this->feed_forward(test_data[i].second).argmax();
    if (actual == expected) {
      total += 1;
    }
  }
  return total;
}

const Matrix Network::cost_derivative(const Matrix& activation, const Matrix& label) const {
  return activation - label;
}

