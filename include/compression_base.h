#ifndef COMPRESSION_BASE_H
#define COMPRESSION_BASE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstdint>

using namespace std;


class CompressionAlgorithm {
    public:
         virtual ~CompressionAlgorithm() = default;
         virtual vector<uint8_t> compress(const vector<uint8_t>& data)=0;
         virtual vector<uint8_t> decompress(const vector<uint8_t>& compressed)=0;
         virtual string getName() const=0;
};
#endif
