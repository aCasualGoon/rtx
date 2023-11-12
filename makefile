# Specify the libraries to link
LNK = -lSDL2 -lGL -lGLEW

# Specify the compiler
CXX = g++

# Specify the root directory of the source files
SRC_DIR = ./src

# Specify additional compilation flags (e.g., -Wall for warnings, -g for debug info)
CXXFLAGS = -Wall -g $(LNK)

# Find all .cpp files in the SRC_DIR
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')

# Object files are generated in the build/obj directory
OBJ_DIR = ./build/obj
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Name of the final executable
TARGET = build/bin/main

# Rule to link all object files to the final executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $(TARGET))
	@$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the compiled executable
run: $(TARGET)
	@./$(TARGET)

# Rule to clean all generated object files and the executable
clean:
	@rm -rf build

# Rule to keep the object files and build the executable
keep_obj: $(OBJECTS)
	@mkdir -p $(dir $(TARGET))
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $^

# .PHONY tells make that run, clean, and keep_obj are not files
.PHONY: run clean keep_obj