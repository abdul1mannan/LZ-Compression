# File: Makefile
# Build configuration for LZ compression algorithms

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Iinclude
DEBUG_FLAGS = -g -DDEBUG

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
TESTDIR = test_files

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TARGET = $(BUILDDIR)/compression

# Header dependencies
HEADERS = $(wildcard $(INCDIR)/*.h)

# Default target
.PHONY: all clean test directories debug install uninstall help

all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TESTDIR)

# Build main target
$(TARGET): $(OBJECTS)
	@echo "🔗 Linking executable..."
	$(CXX) $(OBJECTS) -o $@
	@echo "✅ Build complete: $(TARGET)"

# Compile object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@echo "🔨 Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Clean build files
clean:
	@echo "🧹 Cleaning build files..."
	rm -rf $(BUILDDIR)
	rm -f $(TESTDIR)/*.compressed
	rm -f $(TESTDIR)/*_decompressed.txt
	@echo "✅ Clean complete"

# Run tests
test: $(TARGET)
	@echo "🧪 Running compression tests..."
	./$(TARGET)

# Install to system (optional)
install: $(TARGET)
	@echo "📦 Installing to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/lz_compression
	@echo "✅ Installation complete"

# Uninstall from system
uninstall:
	@echo "🗑️  Uninstalling..."
	sudo rm -f /usr/local/bin/lz_compression
	@echo "✅ Uninstall complete"

# Show help
help:
	@echo "🔧 Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  debug    - Build with debug symbols"
	@echo "  clean    - Remove build files"
	@echo "  test     - Build and run tests"
	@echo "  install  - Install to system PATH"
	@echo "  uninstall- Remove from system"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "📁 Project structure:"
	@echo "  $(INCDIR)/     - Header files"
	@echo "  $(SRCDIR)/     - Source files"
	@echo "  $(BUILDDIR)/   - Build output"
	@echo "  $(TESTDIR)/    - Test files"

# Dependency tracking
-include $(OBJECTS:.o=.d)

$(BUILDDIR)/%.d: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MM -MT $(@:.d=.o) $< > $@