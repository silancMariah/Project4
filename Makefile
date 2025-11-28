# Compiler
CC = gcc

# Paths
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Output
TARGET = $(BUILD_DIR)/pong.elf

# Flags
CFLAGS = -I$(INC_DIR) -Wall -Wextra

# Default rule
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
