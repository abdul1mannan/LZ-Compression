#include "bit_utils.h"

using namespace std;


BitWriter::BitWriter(vector<uint8_t>& out) : output(out), buffer(0), bitCount(0) {}

void BitWriter::writeBits(uint32_t value, int bits) {
    while (bits > 0) {
        int bitsToWrite = min(bits, 8 - bitCount);
        buffer |= ((value >> (bits - bitsToWrite)) & ((1 << bitsToWrite) - 1)) << (8 - bitCount - bitsToWrite);
        bitCount += bitsToWrite;
        bits -= bitsToWrite;
        
        if (bitCount == 8) {
            output.push_back(buffer);
            buffer = 0;
            bitCount = 0;
        }
    }
}

void BitWriter::flush() {
    if (bitCount > 0) {
        output.push_back(buffer);
        buffer = 0;
        bitCount = 0;
    }
}


BitReader::BitReader(const vector<uint8_t>& in) : input(in), bytePos(0), bitPos(0) {}

uint32_t BitReader::readBits(int bits) {
    uint32_t result = 0;
    while (bits > 0 && bytePos < input.size()) {
        int bitsToRead = min(bits, 8 - bitPos);
        uint8_t mask = (1 << bitsToRead) - 1;
        result = (result << bitsToRead) | ((input[bytePos] >> (8 - bitPos - bitsToRead)) & mask);
        bitPos += bitsToRead;
        bits -= bitsToRead;
        
        if (bitPos == 8) {
            bytePos++;
            bitPos = 0;
        }
    }
    return result;
}

bool BitReader::hasMoreBits() const {
    return bytePos < input.size() || bitPos > 0;
}