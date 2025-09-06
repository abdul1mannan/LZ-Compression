#include "compression_utils.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>

using namespace std;

void CompressionUtils::testAlgorithm(unique_ptr<CompressionAlgorithm> algo, 
                                     const vector<uint8_t>& testData) {
    cout << "\n" << string(50, '=') << "\n";
    cout << "Testing " << algo->getName() << " Algorithm\n";
    cout << string(50, '=') << "\n";
    cout << "Original size: " << testData.size() << " bytes\n";
    
    auto compressed = algo->compress(testData);
    cout << "Compressed size: " << compressed.size() << " bytes\n";
    
    printCompressionStats(algo->getName(), testData.size(), compressed.size());
    
    auto decompressed = algo->decompress(compressed);
    
    bool isCorrect = (testData == decompressed);
    cout << "Decompression: " << (isCorrect ? "SUCCESS ✓" : "FAILED ✗") << "\n";
    
    if (!isCorrect) {
        cout << "ERROR: Decompressed size: " << decompressed.size() << " bytes\n";
        cout << "ERROR: Expected size: " << testData.size() << " bytes\n";
    }
}

vector<uint8_t> CompressionUtils::loadFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot open file: " + filename);
    }
    
    return vector<uint8_t>((istreambuf_iterator<char>(file)),
                          istreambuf_iterator<char>());
}

void CompressionUtils::saveFile(const string& filename, const vector<uint8_t>& data) {
    ofstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot create file: " + filename);
    }
    
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

vector<uint8_t> CompressionUtils::stringToVector(const string& str) {
    return vector<uint8_t>(str.begin(), str.end());
}

string CompressionUtils::vectorToString(const vector<uint8_t>& data) {
    return string(data.begin(), data.end());
}

void CompressionUtils::printCompressionStats(const string& algorithmName,
                                            size_t originalSize, size_t compressedSize) {
    double ratio = (double)compressedSize / originalSize * 100.0;
    double savings = (1.0 - (double)compressedSize / originalSize) * 100.0;
    
    cout << fixed << setprecision(2);
    cout << "Compression ratio: " << ratio << "%\n";
    cout << "Space savings: " << savings << "%\n";
    cout << "Size reduction: " << (originalSize - compressedSize) << " bytes\n";
}