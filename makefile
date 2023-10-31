# Specify the libraries to link
LNK = -lSDL2 -lGL -lGLEW

# Specify the compiler
CXX = g++

# Specify the root directory of the source files
SRC_DIR = ./src

# Specify additional compilation flags (e.g., -Wall for warnings, -g for debug info)
CXXFLAGS = -Wall -g $(LNK)

# Find all .cpp files in the SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files are generated in the same directory as their corresponding source files
OBJECTS = $(SOURCES:.cpp=.o)

# Name of the final executable
TARGET = main

# Rule to link all object files to the final executable
$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm $(OBJECTS)

# Rule to compile each source file into an object file
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the compiled executable
run: $(TARGET)
	@./$(TARGET)

# Rule to clean all generated object files and the executable
clean:
	@rm -f $(OBJECTS) $(TARGET)

# Rule to keep the object files and build the executable
keep_obj: $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $^

# .PHONY tells make that run, clean, and keep_obj are not files
.PHONY: run clean keep_obj
