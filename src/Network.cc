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

Network::Network(const std::vector<Matrix>& _weights, const std::vector<Matrix>& _biases, const Cost* _cost) {
  this->weights = _weights;
  this->biases = _biases;
  this->cost = _cost;
  this->num_layers = _weights.size();
  this->cost = _cost;
}

Network::Network(const std::vector<std::size_t>& sizes, const Cost* _cost) {
  this->num_layers = sizes.size() - 1;
  this->sizes = sizes;
  this->biases = std::vector<Matrix>(sizes.size() - 1);
  this->weights = std::vector<Matrix>(sizes.size() - 1);
  for (unsigned int size = 1; size < sizes.size(); ++size) {
    const std::size_t left = size - 1;
    this->weights[left] = Matrix(sizes[left], sizes[size], gaussian_random_generator);
    this->biases[left] = Matrix(sizes[size], 1, gaussian_random_generator);
  }
  this->cost = _cost;
}

const Matrix Network::feed_forward(const Matrix& input) const {
  Matrix output = input;
  for (unsigned int index = 0; index < this->num_layers; ++index) {
    output = (this->weights[index].transpose().product(output) + this->biases[index]).sigmoid();
  }
  return output;
}

void Network::SGD(const MnistData& training_data, const std::size_t& epochs, const std::size_t& mini_batch_size, const double eta, const MnistData& test_data) {
  const std::size_t n = training_data.size();
  for (unsigned int j = 0; j < epochs; ++j) {
    std::clock_t start_epoch = std::clock();
    std::vector<std::pair<Matrix, Matrix>> randomized_data = training_data.randomize();
    std::vector<std::vector<std::pair<Matrix, Matrix>>> mini_batches(0);
    for (unsigned int k = 0; k < n; k += mini_batch_size) {
      std::vector<std::pair<Matrix, Matrix>> mini_batch;
      for (unsigned int l = 0; l < mini_batch_size; ++l) {
        mini_batch.push_back(randomized_data[k + l]);
      }
      mini_batches.push_back(mini_batch);
    }
    for (unsigned int i = 0; i < mini_batches.size(); ++i) {
      this->update_mini_batch(mini_batches[i], eta);
    }
    int evaluation = this->evaluate(test_data);
    printf("Epoch %u: %d / %lu (%li)\n", j, evaluation, test_data.size(), std::clock() - start_epoch);
  }
}

void Network::update_mini_batch(const std::vector<std::pair<Matrix, Matrix>>& mini_batch, const double eta) {
  std::vector<Matrix> nabla_b(this->num_layers);
  std::vector<Matrix> nabla_w(this->num_layers);
  for (unsigned int i = 0; i < this->num_layers; ++i) {
    nabla_b[i] = Matrix::zeros(this->biases[i].getRows(), this->biases[i].getCols());
    nabla_w[i] = Matrix::zeros(this->weights[i].getRows(), this->weights[i].getCols());
  }

  for (auto batch: mini_batch) {
    std::pair<std::vector<Matrix>, std::vector<Matrix>> delta_nablas = this->backprop(batch.first, batch.second);
    std::vector<Matrix> delta_nabla_b = delta_nablas.first;
    std::vector<Matrix> delta_nabla_w = delta_nablas.second;
    for (unsigned int i = 0; i < this->num_layers; ++i) {
      nabla_b[i] += delta_nabla_b[i];
      nabla_w[i] += delta_nabla_w[i];
    }
  }
  for (unsigned int i = 0; i < this->num_layers; ++i) {
    this->weights[i] += (-eta / mini_batch.size()) * nabla_w[i];
    this->biases[i] += (-eta / mini_batch.size()) * nabla_b[i];
  }
}

const std::pair<std::vector<Matrix>, std::vector<Matrix>> Network::backprop(const Matrix& label, const Matrix& image) const {
  std::vector<Matrix> nabla_b(this->num_layers);
  std::vector<Matrix> nabla_w(this->num_layers);
  for (unsigned int i = 0; i < this->num_layers; ++i) {
    nabla_b[i] = Matrix::zeros(this->biases[i].getRows(), this->biases[i].getCols());
    nabla_w[i] = Matrix::zeros(this->weights[i].getRows(), this->weights[i].getCols());
  }

  Matrix activation = image;
  std::vector<Matrix> activations(1, activation);
  std::vector<Matrix> zs(this->num_layers);
  zs.reserve(this->num_layers);
  for (unsigned int i = 0; i < this->num_layers; ++i) {
    Matrix z = this->weights[i].transpose().product(activation) + this->biases[i];
    zs[i] = z;
    activation = z.sigmoid();
    activations.push_back(activation);
  }

  Matrix delta = this->cost->delta(zs[zs.size() - 1], activations[activations.size() - 1], label);
  nabla_b[nabla_b.size() - 1] = delta;
  nabla_w[nabla_w.size() - 1] = activations[activations.size() - 2].product(delta.transpose());
  for (unsigned int l = 2; l < this->num_layers + 1; ++l) {
    delta = this->weights[this->weights.size() + 1 - l].product(delta) * zs[zs.size() - l].sigmoid_prime();
    nabla_b[nabla_b.size() - l] = delta;
    nabla_w[nabla_w.size() - l] = activations[activations.size() - l - 1].product(delta.transpose());
  }
  return std::make_pair(nabla_b, nabla_w);
}

int Network::evaluate(const MnistData& data) const {
  std::vector<std::pair<Matrix, Matrix>> test_data = data.get();
  unsigned int total = 0;
  for (unsigned int i = 0; i < test_data.size(); ++i) {
    const std::size_t expected = test_data[i].first.argmax();
    const std::size_t actual = this->feed_forward(test_data[i].second).argmax();
    if (actual == expected) {
      total += 1;
    }
  }
  return total;
}
