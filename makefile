CC=gcc
CFLAGS=-Wall -g -Wno-format
TARGET=sm_hash_tool
SRC_DIR=src

ifeq ($(OS),Windows_NT)
    TARGET = sm_hash_tool.exe
	CC=clang
endif

all:  $(SRC_DIR)/*.c
	@$(CC) $(CFLAGS) $(SRC_DIR)/*.c -o $(TARGET)

clean:
	@rm -f $(TARGET)
