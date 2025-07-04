# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDLIBS = -lcheck -lsubunit -lm

# Source files
SRCS = tests/test_main.c tests/test_capture.c tests/test_filter.c src/capture.c src/filter.c
TARGET = test_capture

# Default target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $@ $(SRCS) $(CFLAGS) $(LDLIBS)

# Clean target
clean:
	rm -f $(TARGET)
