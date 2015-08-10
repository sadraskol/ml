/*
 * MnistParser.h
 *
 *  Created on: 2 août 2015
 *      Author: thomas
 */

#ifndef MNISTPARSER_H_
#define MNISTPARSER_H_

#include "Matrix.h"
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace neurons {

  class MnistLabelParser {
    public:
      MnistLabelParser(const std::string& file_location) {
        this->file_location = file_location;
      }

      const Matrix getLabel(const std::size_t& index) const {
        int label = getLabelAsInt(index);
        const std::vector<double> data = vectorize(label);
        return Matrix(10, 1, data);
      }

      virtual ~MnistLabelParser() {}
    private:
      int getLabelAsInt(const std::size_t& index) const {
        if (8 + index < 8 || 8 + index > (unsigned int) this->file_size()) {
          throw std::invalid_argument("index too large");
        }
        std::ifstream label_file(this->file_location, std::ifstream::binary);
        return label_file.seekg(8 + index).get();
      }
      const std::vector<double> vectorize(const int& label) const {
        if (label >= 0) {
          std::vector<double> result(10, 0);
          result[label] = 1;
          return result;
        } else {
          return std::vector<double>(10, 0);
        }
      }
      const std::ifstream::pos_type file_size() const {
        std::ifstream in(this->file_location, std::ifstream::ate | std::ifstream::binary);
        return in.tellg(); 
      }
      std::string file_location;
  };

  class MnistImageParser {
    public:
      MnistImageParser(const std::string& file_location) {
        this->file_location = file_location;
      }

      const std::vector<double> getImage(const std::size_t& index) const {
        if (16 + index < 16 || 16 + index * 784 > static_cast<std::size_t>(this->file_size())) {
          throw std::invalid_argument("index too large");
        }
        std::ifstream label_file(this->file_location, std::ifstream::binary);
        label_file.seekg(16 + index * 784);
        char buffer[784];
        label_file.read(buffer, 784);
        std::vector<double> result(784);
        for (int i = 0; i < 784; i++) {
          result[i] = static_cast<double>(static_cast<unsigned char>(buffer[i])) / 255;
        }
        return result;
      }

      virtual ~MnistImageParser() {}
    private:
      int file_size() const {
        std::ifstream in(this->file_location, std::ifstream::ate | std::ifstream::binary);
        return in.tellg(); 
      }
      std::string file_location;
  };

  class MnistData {
    public:
      MnistData(const std::size_t& lower_bound, const std::size_t& upped_bound): min(lower_bound), max(upped_bound) {
        this->data = std::vector<std::pair<Matrix, std::vector<double>>>(this->size());
        for (std::size_t i = 0; i < this->size(); i++) {
          this->data[i] = std::make_pair(this->getLabel(i), this->getImage(i));
        }
      }

      virtual ~MnistData() {}

      const Matrix getLabel(const std::size_t& index) const {
        return labels.getLabel(this->min + index);
      }

      const std::vector<double> getImage(const std::size_t& index) const {
        return images.getImage(this->min + index);
      }

      std::size_t size() const {
        return this->max - this->min;
      }

      const std::vector<std::pair<Matrix, std::vector<double>>> randomize() const {
        std::vector<std::pair<Matrix, std::vector<double>>> copy = this->data;
        // TODO give a random number generator
        std::random_shuffle(copy.begin(), copy.end());
        return copy;
      };

    private:
      std::vector<std::pair<Matrix, std::vector<double>>> data;
      std::size_t min, max;
      MnistLabelParser labels = MnistLabelParser("data/train-labels-idx1-ubyte");
      MnistImageParser images = MnistImageParser("data/train-images-idx3-ubyte");
  };

} /* namespace neurons */

#endif /* MNISTPARSER_H_ */
