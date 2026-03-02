# compiler
CC = gcc
CFLAGS = -Wall -Wextra --pedantic -O2 -I$(INCLUDE_DIR)

# directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/main

all: $(TARGET)

# link object files to create the binary
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# compile .c to .o into build dir
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# create necessary directories
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# clean build and binary files
clean: rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
