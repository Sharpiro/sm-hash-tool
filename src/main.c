#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 500

extern const uint64_t LOOKUP_TABLE[256];

int main() {
  char user_input[BUFFER_SIZE] = {};
  // FILE *file = fopen("test_input.txt", "r");
  fgets(user_input, BUFFER_SIZE, stdin);

  uint64_t hex_value = 0xc96c5795d7870f42;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    char current_char = user_input[i];
    if (current_char == 0 || current_char == '\r' || current_char == '\n') {
      break;
    }

    if (current_char == '/' || current_char == '\\') {
      current_char = '/';
      if (i == 0) {
        continue;
      }

      char next_char = user_input[i + 1];
      while (next_char == '/' || next_char == '\\') {
        i++;
        next_char = user_input[i + 1];
      }
      if (next_char == 0 || next_char == '\r' || next_char == '\n') {
        break;
      }
    }

    uint8_t table_index = current_char + ' ';
    if ((uint8_t)(current_char - 'A') >= 0x1a) {
      table_index = current_char;
    }
    hex_value = LOOKUP_TABLE[table_index ^ (uint8_t)hex_value] ^ hex_value >> 8;
  }

  uint64_t hex_value_display = hex_value >> 2 | 0x8000000000000000;
  printf("%llu\n", hex_value_display);
}
