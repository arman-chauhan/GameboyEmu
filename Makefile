CC := clang

SRC_DIR := ./src
BIN_DIR := ./build
INC_DIR := ./include
OBJS_DIR := $(BIN_DIR)/objs
LIB = -Llib -lraylib

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

CFLAGS := -I$(INC_DIR)  -Wall -Wextra -Wshadow -pedantic -Werror
LDFLAGS := $(LIB)

TARGET := $(BIN_DIR)/gameboy

PLATFORM := $(shell uname)
ifeq ($(PLATFORM), Darwin)
	LDFLAGS += -framework Cocoa -framework IOKit
else ifeq ($(PLATFORM), Linux)
	# Add any Linux-specific flags here if needed
	# LDFLAGS +=
endif

# Default target: build the target executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean build files
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
