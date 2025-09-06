#ifndef LZSS_H
#define LZSS_H

#include "compression_base.h"
#include "bit_utils.h"
#include <algorithm>

using namespace std;

class LZSS : public CompressionAlgorithm {
private:
    static const int WINDOW_SIZE = 4096;
    static const int LOOKAHEAD_SIZE = 18;
    static const int MIN_MATCH_LENGTH = 3;

    struct Match {
        int offset;
        int length;
        
        Match() : offset(0), length(0) {}
        Match(int off, int len) : offset(off), length(len) {}
    };

    Match findLongestMatch(const vector<uint8_t>& data, int pos);
    bool isMatchBeneficial(const Match& match);

public:
    vector<uint8_t> compress(const vector<uint8_t>& data) override;
    vector<uint8_t> decompress(const vector<uint8_t>& compressed) override;
    string getName() const override;
};

#endif 