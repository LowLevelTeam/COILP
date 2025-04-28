CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lcoil -lnof # /usr/local/lib/libcoil.a /usr/local/lib/libnof.a 
SRC_DIR = src/
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Binary name
TARGET = $(BIN_DIR)/cop

# Phony targets
.PHONY: all clean directories

# Default target
all: directories $(TARGET)

# Create directories if they don't exist
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)