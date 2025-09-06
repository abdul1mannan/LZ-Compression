#ifndef COMPRESSION_UTILS_H
#define COMPRESSION_UTILS_H

#include "compression_base.h"
#include <memory>

using namespace std;

class CompressionUtils
{
public:
    static void testAlgorithm(unique_ptr<CompressionAlgorithm> algo,
                              const vector<uint8_t> &testData);
    static vector<uint8_t> loadFile(const string &filename);
    static void saveFile(const string &filename, const vector<uint8_t> &data);
    static vector<uint8_t> stringToVector(const string &str);
    static string vectorToString(const vector<uint8_t> &data);
    static void printCompressionStats(const string &algorithmName,
                                      size_t originalSize, size_t compressedSize);
};

#endif
