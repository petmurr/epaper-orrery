
# VPATH = src tells make where to look
# %.o: %.cpp explicitly compiles each source
# $^ all object files
# $@ target name

# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall

# Directories
SRC_DIR   := src
BUILD_DIR := build

# Files
SOURCES := main.cpp utils.cpp
OBJECTS := $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
TARGET  := $(BUILD_DIR)/out

# Tell make where to find source files
VPATH := $(SRC_DIR)

# Default target
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@

# Compile .cpp -> .o
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
