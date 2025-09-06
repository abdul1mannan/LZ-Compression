#include "lz77.h"

using namespace std;

LZ77::Match LZ77::findLongestMatch(const vector<uint8_t>& data, int pos) {
    Match bestMatch;
    
    if (pos < data.size()) {
        bestMatch.nextChar = data[pos];
    }
    
    int searchStart = max(0, pos - WINDOW_SIZE);
    int maxLength = min(LOOKAHEAD_SIZE, (int)data.size() - pos);
    
    for (int i = searchStart; i < pos; i++) {
        int length = 0;
        while (length < maxLength && 
               pos + length < data.size() && 
               data[i + length] == data[pos + length]) {
            length++;
        }
        
        if (length >= MIN_MATCH_LENGTH && length > bestMatch.length) {
            bestMatch.offset = pos - i;
            bestMatch.length = length;
            if (pos + length < data.size()) {
                bestMatch.nextChar = data[pos + length];
            }
        }
    }
    
    return bestMatch;
}

vector<uint8_t> LZ77::compress(const vector<uint8_t>& data) {
    vector<uint8_t> compressed;
    BitWriter writer(compressed);
    
    int pos = 0;
    while (pos < data.size()) {
        Match match = findLongestMatch(data, pos);
        
        if (match.length >= MIN_MATCH_LENGTH) {
            // Write match flag (1), offset (12 bits), length (4 bits)
            writer.writeBits(1, 1);
            writer.writeBits(match.offset, 12);
            writer.writeBits(match.length - MIN_MATCH_LENGTH, 4);
            pos += match.length;
        } else {
            // Write literal flag (0) and character (8 bits)
            writer.writeBits(0, 1);
            writer.writeBits(data[pos], 8);
            pos++;
        }
    }
    
    writer.flush();
    return compressed;
}

vector<uint8_t> LZ77::decompress(const vector<uint8_t>& compressed) {
    vector<uint8_t> decompressed;
    BitReader reader(compressed);
    
    while (reader.hasMoreBits()) {
        uint32_t flag = reader.readBits(1);
        
        if (flag == 1) {
            // Match
            uint32_t offset = reader.readBits(12);
            uint32_t length = reader.readBits(4) + MIN_MATCH_LENGTH;
            
            if (offset > 0 && offset <= decompressed.size()) {
                int startPos = decompressed.size() - offset;
                for (int i = 0; i < length; i++) {
                    if (startPos + i < decompressed.size()) {
                        decompressed.push_back(decompressed[startPos + i]);
                    }
                }
            }
        } else {
            // Literal
            if (reader.hasMoreBits()) {
                uint32_t character = reader.readBits(8);
                decompressed.push_back(character);
            }
        }
    }
    
    return decompressed;
}

string LZ77::getName() const {
    return "LZ77";
}