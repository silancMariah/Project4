# Compiler
CC = gcc

# Paths
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Files
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/animation.c \
	$(SRC_DIR)/ball.c \
	$(SRC_DIR)/game.c \
	$(SRC_DIR)/gameover.c \
	$(SRC_DIR)/graphics.c \
	$(SRC_DIR)/input.c \
	$(SRC_DIR)/klocka.c \
	$(SRC_DIR)/paddle.c \
	$(SRC_DIR)/points.c \
	$(SRC_DIR)/timer.c \
	$(SRC_DIR)/vga.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Output
TARGET = $(BUILD_DIR)/pong.elf

# Flags
CFLAGS = -I$(INC_DIR) -Wall -Wextra

.PHONY: all clean

# Default rule
all: $(TARGET)

# Build target
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Build object files (ensure build dir exists)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
