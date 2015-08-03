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
} /* namespace neurons */

#endif /* MNISTPARSER_H_ */
