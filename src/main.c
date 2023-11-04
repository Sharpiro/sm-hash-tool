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
    char current_car_resolved = current_char;
    if (current_car_resolved == '/' || current_car_resolved == '\\') {
      if (i == 0) {
        continue;
      }

      int slash_index = i;
      while (current_char == '/' || current_char == '\\') {
        slash_index++;
        current_char = user_input[slash_index];
      }
      i = slash_index - 1;
      current_car_resolved = '/';
    }

    if (current_char == 0 || current_char == '\r' || current_char == '\n') {
      break;
    }

    uint8_t table_index = current_car_resolved + ' ';
    if ((uint8_t)(current_car_resolved - 'A') >= 0x1a) {
      table_index = current_car_resolved;
    }
    hex_value = LOOKUP_TABLE[table_index ^ (uint8_t)hex_value] ^ hex_value >> 8;
  }

  uint64_t hex_value_display = hex_value >> 2 | 0x8000000000000000;
  printf("%llu\n", hex_value_display);
}
