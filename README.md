# File: README.md
# Advanced LZ Compression Algorithms

A high-performance implementation of LZ77, LZSS, and LZ78 compression algorithms in C++17.

## 🚀 Features

- **LZ77**: Sliding window compression with configurable parameters
- **LZSS**: Improved LZ77 with efficiency optimization
- **LZ78**: Dictionary-based compression algorithm
- **Bit-level I/O**: Efficient bit packing for optimal compression
- **File operations**: Complete file compression/decompression utilities
- **Performance testing**: Built-in benchmarking and validation

## 📁 Project Structure

```
lz_compression/
├── include/                 # Header files
│   ├── compression_base.h   # Base classes and interfaces
│   ├── bit_utils.h         # Bit-level I/O utilities
│   ├── compression_utils.h  # Testing and file utilities
│   ├── lz77.h              # LZ77 algorithm
│   ├── lzss.h              # LZSS algorithm
│   └── lz78.h              # LZ78 algorithm
├── src/                    # Source files
│   ├── bit_utils.cpp       # Bit utilities implementation
│   ├── compression_utils.cpp # Utilities implementation
│   ├── lz77.cpp            # LZ77 implementation
│   ├── lzss.cpp            # LZSS implementation
│   ├── lz78.cpp            # LZ78 implementation
│   └── main.cpp            # Main program and examples
├── build/                  # Build output directory
├── test_files/             # Test input/output files
├── Makefile               # Build configuration
└── README.md              # This file
```

## 🔧 Building

### Prerequisites
- C++17 compatible compiler (GCC 7+ or Clang 5+)
- Make (optional)

### Using Makefile (Recommended)
```bash
# Build the project
make

# Build with debug symbols
make debug

# Run tests
make test

# Clean build files
make clean

# Show all available targets
make help
```

### Manual Compilation
```bash
# Create directories
mkdir -p build test_files

# Compile with include path
g++ -std=c++17 -O3 -Wall -Wextra -Iinclude \
    src/*.cpp -o build/compression

# Run
./build/compression
```

## 🎯 Usage

### Basic Usage
```cpp
#include "lz77.h"
#include "compression_utils.h"

// Load file
auto data = CompressionUtils::loadFile("input.txt");

// Compress with LZ77
auto compressor = make_unique<LZ77>();
auto compressed = compressor->compress(data);

// Save compressed file
CompressionUtils::saveFile("output.lz77", compressed);

// Decompress
auto decompressed = compressor->decompress(compressed);
CompressionUtils::saveFile("restored.txt", decompressed);
```

### Command Line
```bash
# Run all algorithm tests
./build/compression

# Output files will be created in test_files/
```

## 📊 Algorithm Comparison

| Algorithm | Approach | Best For | Compression Ratio |
|-----------|----------|----------|-------------------|
| **LZ77** | Sliding window | General purpose, simple patterns | Good |
| **LZSS** | Improved LZ77 | Better efficiency, avoids short matches | Better |
| **LZ78** | Dictionary-based | Diverse repeating patterns | Variable |

## ⚡ Performance Features

- **Bit-level I/O**: Minimal storage overhead
- **Configurable parameters**: Adjustable window sizes and match lengths
- **Efficient matching**: Optimized longest match finding
- **Memory efficient**: Vector-based implementation
- **Error handling**: Robust validation and error recovery

## 🔬 Test Results

The implementation includes comprehensive testing with:
- Pattern recognition validation
- Compression ratio analysis
- Performance timing measurements
- Round-trip integrity verification

Example output:
```
Testing LZ77 Algorithm
==================================================
Original size: 523 bytes
Compressed size: 312 bytes
Compression ratio: 59.66%
Space savings: 40.34%
Decompression: SUCCESS ✓
```

## 🚀 Optimization Opportunities

### Current Optimizations
- Bit-level I/O for minimal overhead
- Configurable algorithm parameters
- Efficient pattern matching algorithms
- Memory-efficient data structures

### Potential Improvements
- Hash tables for O(1) string matching
- Multi-threading for large files
- Adaptive parameters based on file type
- Suffix arrays for advanced pattern matching
- Entropy encoding integration

## 📝 API Reference

### Core Classes

**CompressionAlgorithm** (Base)
```cpp
virtual vector<uint8_t> compress(const vector<uint8_t>& data) = 0;
virtual vector<uint8_t> decompress(const vector<uint8_t>& compressed) = 0;
virtual string getName() const = 0;
```

**LZ77, LZSS, LZ78**
- Inherit from CompressionAlgorithm
- Configurable window sizes and parameters
- Optimized for different use cases

**CompressionUtils**
```cpp
static vector<uint8_t> loadFile(const string& filename);
static void saveFile(const string& filename, const vector<uint8_t>& data);
static void testAlgorithm(unique_ptr<CompressionAlgorithm> algo, const vector<uint8_t>& testData);
```

## 🔧 Configuration

Algorithm parameters can be modified in the header files:

```cpp
// In lz77.h and lzss.h
static const int WINDOW_SIZE = 4096;        // Sliding window size
static const int LOOKAHEAD_SIZE = 18;       // Look-ahead buffer size
static const int MIN_MATCH_LENGTH = 3;      // Minimum match length

// In lz78.h
static const int MAX_DICT_SIZE = 65536;     // Maximum dictionary size
```

## 📄 License

This project is provided as-is for educational and research purposes. Feel free to use and modify according to your needs.

## 🤝 Contributing

Contributions are welcome! Areas for improvement:
- Performance optimizations
- Additional compression algorithms
- Better error handling
- Documentation improvements

## 📧 Support

For questions or issues, please refer to the source code comments and algorithm documentation.