/*
 * MnistParser.h
 *
 *  Created on: 2 août 2015
 *      Author: thomas
 */

#ifndef MNISTPARSER_H_
#define MNISTPARSER_H_

#include <string>
#include <fstream>
#include <iostream>

namespace neurons {

    class MnistLabelParser {
    public:
        MnistLabelParser(const std::string& file_location) {
            this->file_location = file_location;
        }

        int getLabel(const std::size_t& index) const {
            std::ifstream label_file(this->file_location, std::ifstream::binary);
            return label_file.seekg(8 + index).get();
        }

        virtual ~MnistLabelParser() {}
    private:
        std::string file_location;
    };
} /* namespace neurons */

#endif /* MNISTPARSER_H_ */
