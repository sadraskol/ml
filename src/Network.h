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
#include "Matrix.h"

class Network {
public:
	Network(const std::vector<std::size_t>& sizes) {
        this->num_layers = sizes.size();
        this->sizes = sizes;
        this->biases = std::vector<void *>(0);
        std::for_each(sizes.begin() + 1, sizes.end(), [this, sizes](const std::size_t& size) {
            std::size_t const& _size = size;
            this->biases.push_back(new Matrix<_size, 1>([]() {
                return std::normal_distribution<double>(0.0, 1.0);
            });
        });
	}
	virtual ~Network() {}

private:
    std::size_t num_layers;
    std::vector<std::size_t> sizes;
    std::vector<void *> biases;
};

#endif /* NETWORK_H_ */
