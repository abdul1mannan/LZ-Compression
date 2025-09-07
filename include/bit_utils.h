#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

class BitWriter {
    private:
    vector<uint8_t>& output;
    uint8_t buffer;
    int bitCount;

    public:
    BitWriter(vector<uint8_t>& out);
    void writeBits(uint32_t value, int bits);
    void flush();

};


class BitReader {
    private:
    const vector<uint8_t>& input;
    size_t bytePos;
    int bitPos;
    public:
    BitReader(const vector<uint8_t>& in);
    uint32_t readBits(int bits);
    bool hasMoreBits() const;
};
#endif