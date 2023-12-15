# Makefile configuration
CC :=ccache g++
CFLAGS := -g -fuse-ld=gold -Wall
# INCLUDES := 
# LDFLAGS := 
LDLIBS := -lSDL2 -lGL -lGLEW
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
TARGET := $(BIN_DIR)/rtx

# Automatically find all .cpp files in SRC_DIR and its subdirectories
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
# Replace .cpp from SOURCES with .o and change SRC_DIR to OBJ_DIR
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Verbose control
VERBOSE := 0
ifeq ($(VERBOSE),0)
  Q := @
else
  Q :=
endif

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(Q)mkdir -p $(BIN_DIR)
	$(Q)$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

# Compile the source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(Q)mkdir -p $(@D)
	$(Q)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up, removing only object files and keeping the executable
clean:
	$(Q)find $(OBJ_DIR) -type f -name '*.o' -delete
	$(Q)find $(OBJ_DIR) -type d -empty -delete

# Build and then clean up, but keep the executable
cleanbuild: all
	$(Q)$(MAKE) clean

.PHONY: all clean cleanbuild run cleanrun

# make 			  : build the executable
# make clean 	  : remove all object files
# make cleanbuild : build the executable and then remove all object files
# all options are available with VERBOSE=1, e.g., VERBOSE=1 make cleanrun