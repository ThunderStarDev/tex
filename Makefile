# Compiler and base flags
CXX      = g++
BASE_FLAGS = -std=c++17 -Wall -Wextra

DEBUG_FLAGS   = -g -O0
RELEASE_FLAGS = -O2

# Project name
TARGET   = tex
SOURCES  = $(TARGET).cpp

# Default target
all: release

# Release build
release: CXXFLAGS = $(BASE_FLAGS) $(RELEASE_FLAGS)
release: $(TARGET)

# Debug build
debug: CXXFLAGS = $(BASE_FLAGS) $(DEBUG_FLAGS)
debug: $(TARGET)

# Build the binary
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean up
clean:
	rm -f $(TARGET) *.o

# Install (optional prefix)
PREFIX ?= /usr/local
install: $(TARGET)
	sudo cp $(TARGET) $(PREFIX)/bin/

.PHONY: all release debug clean install
