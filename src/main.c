#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 500

extern const uint64_t LOOKUP_TABLE[256];

void process_char(const char character, uint64_t *hex_value) {
  uint8_t table_index = character + ' ';
  if ((uint8_t)(character - 'A') >= 0x1a) {
    table_index = character;
  }
  *hex_value =
      LOOKUP_TABLE[table_index ^ (uint8_t)*hex_value] ^ *hex_value >> 8;
}

int main() {
  char user_input[BUFFER_SIZE] = {};
  // FILE *file = fopen("test_input.txt", "r");
  fgets(user_input, BUFFER_SIZE, stdin);

  uint64_t hex_value = 0xc96c5795d7870f42;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    char current_char = user_input[i];
    char next_char = current_char;
    char selected_char = '/';
    if (current_char == '/' || current_char == '\\') {
      while (next_char == '/' || next_char == '\\') {
        i++;
        next_char = user_input[i];
      }
      i--;
    } else {
      selected_char = current_char;
    }

    if (next_char == 0 || next_char == '\r' || next_char == '\n') {
      break;
    }

    process_char(selected_char, &hex_value);
  }

  uint64_t hex_value_display = hex_value >> 2 | 0x8000000000000000;
  printf("%llu\n", hex_value_display);
}
