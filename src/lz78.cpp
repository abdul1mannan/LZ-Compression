#include "lz78.h"

using namespace std;

vector<uint8_t> LZ78::compress(const vector<uint8_t>& data) {
    vector<uint8_t> compressed;
    BitWriter writer(compressed);
    
    vector<DictEntry> dictionary;
    dictionary.push_back(DictEntry()); // Index 0 is empty
    
    unordered_map<string, int> stringToIndex;
    
    int pos = 0;
    while (pos < data.size()) {
        string current;
        int lastIndex = 0;
        
        // Find longest match in dictionary
        while (pos < data.size()) {
            current += static_cast<char>(data[pos]);
            auto it = stringToIndex.find(current);
            if (it != stringToIndex.end()) {
                lastIndex = it->second;
                pos++;
            } else {
                break;
            }
        }
        
        // Output: index + character
        writer.writeBits(lastIndex, 16); // Dictionary index
        if (pos < data.size()) {
            writer.writeBits(data[pos], 8); // Next character
            
            // Add new entry to dictionary if not full
            if (dictionary.size() < MAX_DICT_SIZE) {
                dictionary.push_back(DictEntry(lastIndex, data[pos]));
                stringToIndex[current] = dictionary.size() - 1;
            }
            pos++;
        } else {
            writer.writeBits(0, 8); // End marker
        }
    }
    
    writer.flush();
    return compressed;
}

vector<uint8_t> LZ78::decompress(const vector<uint8_t>& compressed) {
    vector<uint8_t> decompressed;
    BitReader reader(compressed);
    
    vector<string> dictionary;
    dictionary.push_back(""); // Index 0 is empty
    
    while (reader.hasMoreBits()) {
        uint32_t index = reader.readBits(16);
        if (!reader.hasMoreBits()) break;
        
        uint32_t character = reader.readBits(8);
        
        // Handle end of data
        if (character == 0 && index == 0) break;
        
        string entry;
        if (index < dictionary.size()) {
            entry = dictionary[index];
        }
        
        if (character != 0) {
            entry += static_cast<char>(character);
            
            // Add new entry to dictionary if not full
            if (dictionary.size() < MAX_DICT_SIZE) {
                dictionary.push_back(entry);
            }
        }
        
        // Output the string
        for (char c : entry) {
            decompressed.push_back(static_cast<uint8_t>(c));
        }
    }
    
    return decompressed;
}

string LZ78::getName() const {
    return "LZ78";
}