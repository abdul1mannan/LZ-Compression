#ifndef LZ78_H
#define LZ78_H

#include "compression_base.h"
#include "bit_utils.h"
#include <unordered_map>

using namespace std;

class LZ78 : public CompressionAlgorithm {
private:
    struct DictEntry {
        int parent;
        uint8_t character;
        
        DictEntry(int p = -1, uint8_t c = 0) : parent(p), character(c) {}
    };

    static const int MAX_DICT_SIZE = 65536;

public:
    vector<uint8_t> compress(const vector<uint8_t>& data) override;
    vector<uint8_t> decompress(const vector<uint8_t>& compressed) override;
    string getName() const override;
};

#endif 