# Compiler settings
CC ?= gcc
CFLAGS = -std=c11 -Wall -Wextra

# Debug flags
DEBUG_FLAGS = -g -O0 -DDEBUG

# Directories
BUILD_DIR = build
DEBUG_BUILD_DIR = $(BUILD_DIR)/debug
SRC_DIR = src
LIB_DIR = lib

# Automatically find all subdirectories under src for includes
INCLUDES = $(shell find $(SRC_DIR) -type d | sed 's/^/-I/')

# Source files
SOURCES = $(shell find $(SRC_DIR) -name "*.c")
OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)
DEBUG_OBJECTS = $(SOURCES:%.c=$(DEBUG_BUILD_DIR)/%.o)

# Dependency files
DEPS = $(OBJECTS:.o=.d)
DEBUG_DEPS = $(DEBUG_OBJECTS:.o=.d)

# macOS specific frameworks
FRAMEWORKS = -framework IOKit -framework Cocoa -framework OpenGL

# Target executables
TARGET = GameBoy
DEBUG_TARGET = GameBoy_debug

# Default target
all: $(BUILD_DIR) $(TARGET)

# Debug target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_BUILD_DIR) $(DEBUG_TARGET)

# Create build directory structure
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DEBUG_BUILD_DIR):
	mkdir -p $(DEBUG_BUILD_DIR)

# Linking for release build
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIB_DIR)/libraylib.a $(FRAMEWORKS) -o $(TARGET)

# Linking for debug build
$(DEBUG_TARGET): $(DEBUG_OBJECTS)
	$(CC) $(DEBUG_OBJECTS) $(LIB_DIR)/libraylib.a $(FRAMEWORKS) -o $(DEBUG_TARGET)

# Compilation for release build
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation for debug build
$(DEBUG_BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Run with LLDB
lldb: debug
	lldb ./$(DEBUG_TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(DEBUG_TARGET)

# Phony targets
.PHONY: all debug clean lldb

# Dependencies
-include $(DEPS)
-include $(DEBUG_DEPS)
