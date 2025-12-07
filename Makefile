# Compiler/toolchain
# Override TOOLCHAIN=riscv32-unknown-elf- (eller liknande) om du korskompilerar.
# Compiler/toolchain
TOOLCHAIN ?= riscv32-unknown-elf-
CC = $(TOOLCHAIN)gcc
OBJCOPY = $(TOOLCHAIN)objcopy



# Paths
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Files (exclude test/demo programs and wip modules from main build)
SRCS = $(filter-out $(SRC_DIR)/ballTest.c $(SRC_DIR)/spriteTest.c $(SRC_DIR)/flowstate.c $(SRC_DIR)/input.c $(SRC_DIR)/rainball.c,$(wildcard $(SRC_DIR)/*.c))
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Output
TARGET = $(BUILD_DIR)/pong.elf
BIN = $(BUILD_DIR)/main.bin

# Flags
# Default: bygga för riktig hårdvara (VGA + timer). Sätt SIM=0 för ASCII-terminal.
EXTRA_CFLAGS ?=
CFLAGS = -I$(INC_DIR) -Wall -Wextra $(EXTRA_CFLAGS)
LDFLAGS ?=
LDLIBS ?=

ifeq ($(SIM),0)
CFLAGS += -DVGA_SIMULATION
else
CFLAGS += -DUSE_REAL_VGA -DUSE_REAL_TIMER -DVGA_BASE_ADDR=0x08000000
endif

# Lägg till softfloat när du korskompilerar för RISC-V
ifdef SOFTFLOAT
LDLIBS += $(SOFTFLOAT)
endif

.PHONY: all clean

# Default rule
all: $(TARGET) $(BIN)

# Build target
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(TARGET)

# Binary image for dtekv-run
$(BIN): $(TARGET) | $(BUILD_DIR)
	$(OBJCOPY) -O binary $< $@

# Build object files (ensure build dir exists)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) $(BIN)
