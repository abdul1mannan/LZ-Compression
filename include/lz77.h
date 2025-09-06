#ifndef LZ77_H
#define LZ77_H

#include "compression_base.h"
#include "bit_utils.h"
#include <algorithm>

using namespace std;

class LZ77 : public CompressionAlgorithm {
private:
    static const int WINDOW_SIZE = 4096;
    static const int LOOKAHEAD_SIZE = 18;
    static const int MIN_MATCH_LENGTH = 3;

    struct Match {
        int offset;
        int length;
        uint8_t nextChar;
        
        Match() : offset(0), length(0), nextChar(0) {}
        Match(int off, int len, uint8_t next) : offset(off), length(len), nextChar(next) {}
    };

    Match findLongestMatch(const vector<uint8_t>& data, int pos);

public:
    vector<uint8_t> compress(const vector<uint8_t>& data) override;
    vector<uint8_t> decompress(const vector<uint8_t>& compressed) override;
    string getName() const override;
};

#endif 