
# VPATH = src tells make where to look
# %.o: %.cpp explicitly compiles each source
# $^ all object files
# $@ target name

# Compiler and flags
CXX      := g++
CXXFLAGS := -g -Wall

# Directories
SRC_DIR   := src
BUILD_DIR := build

# Includes
# INC_DIR   := include
# INCLUDES := -I$(INC_DIR)

# Libraries
# LIB_DIR  := lib
# LIBS     := -L$(LIB_DIR) -lm -lpthread

# Files
SOURCES := main.cpp epsim.cpp ws.cpp astronomy.c
OBJECTS := $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
TARGET  := $(BUILD_DIR)/out

# Tell make where to find source files
VPATH := $(SRC_DIR)

# Default target
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJECTS)
	$(CXX) $^ $(LIBS) -o $@

# Compile .cpp -> .o
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
