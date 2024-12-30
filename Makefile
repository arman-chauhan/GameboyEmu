# Compiler settings
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

# Debug flags
DEBUG_FLAGS = -g -O0 -DDEBUG

# Directories
BUILD_DIR = build
DEBUG_BUILD_DIR = build/debug
SRC_DIR = src
CPU_DIR = $(SRC_DIR)/cpu
MMU_DIR = $(SRC_DIR)/mmu
PPU_DIR = $(SRC_DIR)/ppu
DEBUG_DIR = $(SRC_DIR)/debug
LIB_DIR = lib

# Include paths
INCLUDES = -I$(SRC_DIR) \
           -I$(CPU_DIR) \
           -I$(MMU_DIR) \
           -I$(PPU_DIR) \
           -I$(DEBUG_DIR)

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c) \
          $(wildcard $(CPU_DIR)/*.c) \
          $(wildcard $(MMU_DIR)/*.c) \
          $(wildcard $(PPU_DIR)/*.c) \
          $(wildcard $(DEBUG_DIR)/*.c)

# Object files
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
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	mkdir -p $(BUILD_DIR)/$(CPU_DIR)
	mkdir -p $(BUILD_DIR)/$(MMU_DIR)
	mkdir -p $(BUILD_DIR)/$(PPU_DIR)
	mkdir -p $(BUILD_DIR)/$(DEBUG_DIR)

# Create debug build directory structure
$(DEBUG_BUILD_DIR):
	mkdir -p $(DEBUG_BUILD_DIR)/$(SRC_DIR)
	mkdir -p $(DEBUG_BUILD_DIR)/$(CPU_DIR)
	mkdir -p $(DEBUG_BUILD_DIR)/$(MMU_DIR)
	mkdir -p $(DEBUG_BUILD_DIR)/$(PPU_DIR)
	mkdir -p $(DEBUG_BUILD_DIR)/$(DEBUG_DIR)

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
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
	rm -f $(DEBUG_TARGET)

# Phony targets
.PHONY: all debug clean lldb

# Dependencies
-include $(DEPS)
-include $(DEBUG_DEPS)

# Generate dependency files for release build
$(BUILD_DIR)/%.d: %.c
	@mkdir -p $(dir $@)
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Generate dependency files for debug build
$(DEBUG_BUILD_DIR)/%.d: %.c
	@mkdir -p $(dir $@)
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(DEBUG_BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$