# Directories
BUILD_DIR = build
SRC_DIR = src

# Compiler
CXX = g++
CXXFLAGS = -Wall -Iinclude

# Find all .cpp files in src/
SRC := $(wildcard $(SRC_DIR)/*.cpp)

# Convert each src/file.cpp → file.o
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Final executable name
TARGET = os_sim

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


# Compile each .cpp → .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp| $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -rf build $(TARGET)

.PHONY: all clean
