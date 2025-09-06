#include "lzss.h"

using namespace std;

LZSS::Match LZSS::findLongestMatch(const vector<uint8_t>& data, int pos) {
    Match bestMatch;
    
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
        }
    }
    
    return bestMatch;
}

bool LZSS::isMatchBeneficial(const Match& match) {
    if (match.length < MIN_MATCH_LENGTH) return false;
    
    // Calculate bits needed for match vs literals
    int matchBits = 1 + 12 + 5; // flag + offset + length
    int literalBits = match.length * 9; // length * (flag + char)
    
    return matchBits < literalBits;
}

vector<uint8_t> LZSS::compress(const vector<uint8_t>& data) {
    vector<uint8_t> compressed;
    BitWriter writer(compressed);
    
    int pos = 0;
    while (pos < data.size()) {
        Match match = findLongestMatch(data, pos);
        
        if (match.length >= MIN_MATCH_LENGTH && isMatchBeneficial(match)) {
            // Write match: flag(1) + offset(12) + length(5)
            writer.writeBits(1, 1);
            writer.writeBits(match.offset, 12);
            writer.writeBits(match.length - MIN_MATCH_LENGTH, 5);
            pos += match.length;
        } else {
            // Write literal: flag(0) + character(8)
            writer.writeBits(0, 1);
            writer.writeBits(data[pos], 8);
            pos++;
        }
    }
    
    writer.flush();
    return compressed;
}

vector<uint8_t> LZSS::decompress(const vector<uint8_t>& compressed) {
    vector<uint8_t> decompressed;
    BitReader reader(compressed);
    
    while (reader.hasMoreBits()) {
        uint32_t flag = reader.readBits(1);
        
        if (flag == 1) {
            // Match
            uint32_t offset = reader.readBits(12);
            uint32_t length = reader.readBits(5) + MIN_MATCH_LENGTH;
            
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

string LZSS::getName() const {
    return "LZSS";
}