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

namespace neurons {
    class Network {
    public:
        explicit Network(const std::vector<std::size_t>& sizes);

        virtual ~Network() {
            this->sizes.clear();
            this->biases.clear();
            this->weights.clear();
        }

        const Matrix feed_forward(const Matrix& input) const;
        const Matrix SGD(training_data, epochs, mini_batch_size, eta, test_data) const;

    private:
        std::size_t num_layers;
        std::vector<std::size_t> sizes;
        std::vector<Matrix*> biases;
        std::vector<Matrix*> weights;
    };
}
#endif /* NETWORK_H_ */
