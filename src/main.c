#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 500

extern const uint64_t HASH_LOOKUP_TABLE[256];

static uint64_t get_hash(char *text);

int main(int argc, char **argv) {
  char input_buffer[BUFFER_SIZE] = {};
  FILE *file;
  if (argc == 2) {
    file = fopen(argv[1], "r");
    if (file == NULL) {
      fprintf(stderr, "err: file not found\n");
      return -1;
    }
  } else {
    file = stdin;
  }

  while (true) {
    char *read_result = fgets(input_buffer, BUFFER_SIZE, file);
    if (read_result == NULL) {
      break;
    }
    if (*read_result == '\r' || *read_result == '\n') {
      break;
    }
    uint64_t hash = get_hash(input_buffer);
    printf("%llu\n", hash);
  }

  fclose(file);
}

static uint64_t get_hash(char *text) {
  uint64_t hash = 0xc96c5795d7870f42;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    char current_char = text[i];
    if (current_char == 0 || current_char == '\r' || current_char == '\n') {
      break;
    }

    if (current_char == '/' || current_char == '\\') {
      current_char = '/';
      if (i == 0) {
        continue;
      }

      char next_char = text[i + 1];
      while (next_char == '/' || next_char == '\\') {
        i++;
        next_char = text[i + 1];
      }
      if (next_char == 0 || next_char == '\r' || next_char == '\n') {
        break;
      }
    }

    uint8_t table_index = current_char + ' ';
    if ((uint8_t)(current_char - 'A') >= 0x1a) {
      table_index = current_char;
    }
    hash = HASH_LOOKUP_TABLE[table_index ^ (uint8_t)hash] ^ hash >> 8;
  }

  uint64_t hash_display = hash >> 2 | 0x8000000000000000;
  return hash_display;
}
