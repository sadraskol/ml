/*
 * Network.h
 *
 *  Created on: 1 août 2015
 *      Author: thomas
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include "Matrix.h"
#include "MnistParser.h"

namespace neurons {
  class Network {
    public:
      Network(const std::vector<std::size_t>& sizes);

      virtual ~Network() {
        this->sizes.clear();
        this->biases.clear();
        this->weights.clear();
      }

      const Matrix feed_forward(const Matrix& input) const;
      void SGD(const MnistData& training_data, const std::size_t& epochs, const std::size_t& mini_batch_size, const double eta, const MnistData& test_data);
      void update_mini_batch(const std::vector<std::pair<Matrix, Matrix>>& data, const double eta);
      const std::pair<std::vector<Matrix>, std::vector<Matrix>> backprop(const Matrix& label, const Matrix& image) const;
      int evaluate(const MnistData& data) const;

      const Matrix cost_derivative(const Matrix& activation, const Matrix& label) const;

    private:
      std::size_t num_layers;
      std::vector<std::size_t> sizes;
      std::vector<Matrix> biases;
      std::vector<Matrix> weights;
  };
}
#endif /* NETWORK_H_ */
