# Compiler settings
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

# Directories
BUILD_DIR = build
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

# Object files (in build directory)
OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Dependency files
DEPS = $(OBJECTS:.o=.d)

# macOS specific frameworks
FRAMEWORKS = -framework IOKit -framework Cocoa -framework OpenGL

# Target executable (in root directory)
TARGET = GameBoy

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory structure
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	mkdir -p $(BUILD_DIR)/$(CPU_DIR)
	mkdir -p $(BUILD_DIR)/$(MMU_DIR)
	mkdir -p $(BUILD_DIR)/$(PPU_DIR)
	mkdir -p $(BUILD_DIR)/$(DEBUG_DIR)

# Linking
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIB_DIR)/libraylib.a $(FRAMEWORKS) -o $(TARGET)

# Compilation
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean

# Dependencies
-include $(DEPS)

# Generate dependency files
$(BUILD_DIR)/%.d: %.c
	@mkdir -p $(dir $@)
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$