/*
 * MnistParser.h
 *
 *  Created on: 2 août 2015
 *      Author: thomas
 */

#ifndef MNISTPARSER_H_
#define MNISTPARSER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace neurons {

    class MnistLabelParser {
    public:
        MnistLabelParser(const std::string& file_location) {
            this->file_location = file_location;
        }

        int getLabel(const std::size_t& index) const {
            if (8 + index < 8 || 8 + index > (unsigned int) this->file_size()) {
                throw std::invalid_argument("index too large");
            }
            std::ifstream label_file(this->file_location, std::ifstream::binary);
            return label_file.seekg(8 + index).get();
        }

        virtual ~MnistLabelParser() {}
    private:
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

        const std::vector<unsigned char> getImage(const std::size_t& index) const {
            if (16 + index < 16 || 16 + index * 784 > (unsigned int) this->file_size()) {
                throw std::invalid_argument("index too large");
            }
            std::ifstream label_file(this->file_location, std::ifstream::binary);
            label_file.seekg(16 + index * 784);
            char result[784];
            label_file.read(result, 784);
            return std::vector<unsigned char>(result, result + sizeof(result) / sizeof(char));
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
        MnistData(const std::size_t& lower_bound, const std::size_t& upped_bound): min(lower_bound), max(upped_bound) {}

        virtual ~MnistData() {}

        int getLabel(const std::size_t& index) const {
            return labels.getLabel(this->min + index);
        }

        const std::vector<unsigned char> getImage(std::size_t index) const {
            return images.getImage(this->min + index);
        }

        int length() const {
            return this->max - this->min;
        }

    private:
        std::size_t min, max;
        MnistLabelParser labels = MnistLabelParser("data/train-labels-idx1-ubyte");
        MnistImageParser images = MnistImageParser("data/train-images-idx3-ubyte");
    };
} /* namespace neurons */

#endif /* MNISTPARSER_H_ */
