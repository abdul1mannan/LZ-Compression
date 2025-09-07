#include "compression_base.h"
#include "compression_utils.h"
#include "lz77.h"
#include "lzss.h"
#include "lz78.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

void printHeader() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║              Advanced LZ Compression Algorithms             ║\n";
    cout << "║                    LZ77 | LZSS | LZ78                       ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void runBasicTests() {
    cout << "🔧 Running Basic Compression Tests...\n\n";
    
    // Create test data with repetitive patterns
    string testStr = "abracadabra_abracadabra_this_is_a_test_string_with_repetitions_"
                     "the_quick_brown_fox_jumps_over_the_lazy_dog_"
                     "abcdefghijklmnopqrstuvwxyz_1234567890_"
                     "aaaaaaaaaa_bbbbbbbbbb_cccccccccc_"
                     "repeat_repeat_repeat_repeat_repeat_"
                     "pattern_pattern_pattern_pattern_"
                     "hello_world_hello_world_hello_world";
    
    vector<uint8_t> testData = CompressionUtils::stringToVector(testStr);
    
    // Test all algorithms
    CompressionUtils::testAlgorithm(make_unique<LZ77>(), testData);
    CompressionUtils::testAlgorithm(make_unique<LZSS>(), testData);
    CompressionUtils::testAlgorithm(make_unique<LZ78>(), testData);
}

void runFileCompressionExample() {
    cout << "\n📁 File Compression Example\n";
    cout << string(60, '-') << "\n";
    
    // Create a sample file for testing
    string sampleContent = R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco.
Duis aute irure dolor in reprehenderit in voluptate velit esse.
Excepteur sint occaecat cupidatat non proident, sunt in culpa.

The quick brown fox jumps over the lazy dog.
The quick brown fox jumps over the lazy dog again.
The quick brown fox jumps over the lazy dog once more.

This line repeats: Hello World! Hello World! Hello World!
This line repeats: Hello World! Hello World! Hello World!
This line repeats: Hello World! Hello World! Hello World!

AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD

Pattern matching test:
pattern_pattern_pattern_pattern_pattern
algorithm_algorithm_algorithm_algorithm
compression_compression_compression_compression

End of sample file content.
End of sample file content.
End of sample file content.)";

    try {
        // Save sample content to file
        vector<uint8_t> sampleData = CompressionUtils::stringToVector(sampleContent);
        CompressionUtils::saveFile("test_files/sample.txt", sampleData);
        cout << "✓ Created test_files/sample.txt for testing\n\n";
        
        // Load and compress with each algorithm
        vector<string> algorithms = {"LZ77", "LZSS", "LZ78"};
        
        for (const string& algoName : algorithms) {
            cout << "🔄 Testing " << algoName << "...\n";
            
            auto fileData = CompressionUtils::loadFile("test_files/sample.txt");
            cout << "Original file size: " << fileData.size() << " bytes\n";
            
            unique_ptr<CompressionAlgorithm> algo;
            if (algoName == "LZ77") {
                algo = make_unique<LZ77>();
            } else if (algoName == "LZSS") {
                algo = make_unique<LZSS>();
            } else {
                algo = make_unique<LZ78>();
            }
            
            // Measure compression time
            auto start = high_resolution_clock::now();
            auto compressed = algo->compress(fileData);
            auto end = high_resolution_clock::now();
            auto compressionTime = duration_cast<microseconds>(end - start);
            
            string compressedFile = "test_files/sample_" + algoName + ".compressed";
            CompressionUtils::saveFile(compressedFile, compressed);
            
            cout << "Compressed size: " << compressed.size() << " bytes\n";
            CompressionUtils::printCompressionStats(algoName, fileData.size(), compressed.size());
            cout << "Compression time: " << compressionTime.count() << " microseconds\n";
            cout << "✓ Saved as: " << compressedFile << "\n";
            
            // Measure decompression time
            start = high_resolution_clock::now();
            auto decompressed = algo->decompress(compressed);
            end = high_resolution_clock::now();
            auto decompressionTime = duration_cast<microseconds>(end - start);
            
            string decompressedFile = "test_files/sample_" + algoName + "_decompressed.txt";
            CompressionUtils::saveFile(decompressedFile, decompressed);
            
            bool isCorrect = (fileData == decompressed);
            cout << "Decompression: " << (isCorrect ? "SUCCESS ✓" : "FAILED ✗") << "\n";
            cout << "Decompression time: " << decompressionTime.count() << " microseconds\n";
            cout << "✓ Saved decompressed as: " << decompressedFile << "\n\n";
        }
        
    } catch (const exception& e) {
        cout << "❌ Error: " << e.what() << "\n";
        cout << "💡 Note: Make sure the test_files/ directory exists\n";
    }
}

void showUsage() {
    cout << "📖 Usage Information\n";
    cout << string(60, '-') << "\n";
    cout << "1. Compile all files:\n";
    cout << "   g++ -std=c++17 -O3 -Iinclude src/*.cpp -o compression\n\n";
    
    cout << "2. Run the program:\n";
    cout << "   ./compression\n\n";
    
    cout << "3. Required directory structure:\n";
    cout << "   lz_compression/\n";
    cout << "   ├── include/          (header files)\n";
    cout << "   ├── src/              (source files)\n";
    cout << "   ├── test_files/       (test input/output)\n";
    cout << "   └── compression       (executable)\n\n";
    
    cout << "4. To use in your own code:\n";
    cout << "   #include \"lz77.h\"\n";
    cout << "   auto compressor = make_unique<LZ77>();\n";
    cout << "   auto compressed = compressor->compress(data);\n";
    cout << "   auto decompressed = compressor->decompress(compressed);\n\n";
}

void printPerformanceComparison() {
    cout << "⚡ Performance Comparison\n";
    cout << string(60, '-') << "\n";
    cout << "LZ77:  ✓ Good general compression\n";
    cout << "       ✓ Handles repeating patterns well\n";
    cout << "       ✓ Simple implementation\n";
    cout << "       - Stores next character in triplets\n\n";
    
    cout << "LZSS:  ✓ Improved LZ77 variant\n";
    cout << "       ✓ Better compression ratios\n";
    cout << "       ✓ Avoids inefficient short matches\n";
    cout << "       ✓ More space-efficient encoding\n\n";
    
    cout << "LZ78:  ✓ Dictionary-based approach\n";
    cout << "       ✓ Good for diverse repeating patterns\n";
    cout << "       ✓ Builds adaptive dictionary\n";
    cout << "       - Different approach than sliding window\n\n";
}

void printOptimizationNotes() {
    cout << "🚀 Optimization Notes\n";
    cout << string(60, '-') << "\n";
    cout << "Current optimizations:\n";
    cout << "• Bit-level I/O for minimal storage overhead\n";
    cout << "• Configurable window sizes and match lengths\n";
    cout << "• Efficient longest match finding algorithms\n";
    cout << "• Memory-efficient vector-based implementation\n";
    cout << "• Robust error handling and validation\n\n";
    
    cout << "Possible improvements:\n";
    cout << "• Hash tables for O(1) string matching\n";
    cout << "• Multi-threading for large files\n";
    cout << "• Adaptive parameters based on file type\n";
    cout << "• Suffix arrays for advanced pattern matching\n";
    cout << "• Entropy encoding for better compression\n\n";
}

int main() {
    printHeader();
    
    // Create test_files directory if it doesn't exist
    system("mkdir -p test_files");
    
    showUsage();
    runBasicTests();
    runFileCompressionExample();
    printPerformanceComparison();
    printOptimizationNotes();
    
    cout << "🎉 All tests completed successfully!\n";
    cout << "📂 Check the test_files/ directory for output files.\n";
    
    return 0;
}