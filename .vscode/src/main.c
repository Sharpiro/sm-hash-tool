#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 500

extern const uint64_t LOOKUP_TABLE[256];

void process_char(char current_char, uint64_t *hex_value) {
  printf("%c\n", current_char);

  // uint64_t table_index = current_char + ' ';
  uint8_t table_index = current_char + ' ';
  if (current_char - 'A' >= 0x1a) {
    table_index = current_char;
  }
  // printf("ti %c\n", table_index);
  *hex_value =
      LOOKUP_TABLE[table_index ^ (uint8_t)*hex_value] ^ *hex_value >> 8;
  // table_index = table_index ^ *hex_value;
  // printf("ti: %llx\n", (uint64_t)table_index);
  // printf("hv: %llx\n", *hex_value);
  // printf("aa: %llx\n", (uint64_t)table_index ^ (uint8_t)*hex_value);
  // *hex_value = (LOOKUP_TABLE[(uint64_t)table_index ^ (uint8_t)*hex_value] ^
  //               (*hex_value >> 8));
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
  printf("done %llu\n", hex_value_display);
}

// uint64_t *build_lookup_table() {
//   uint64_t *lookup_table = malloc(sizeof(lookup_table_buffer));
//   uint64_t current_number;
//   for (int i = 0; i < sizeof(lookup_table_buffer) + 1; i++) {
//   if (i > 0 && i % 8 == 0) {
//     int numbers_index = i / 8;
//     lookup_table[numbers_index] = current_number;
//     printf("0x%016llx\n", current_number);
//     current_number = 0;
//   }
//   uint64_t shifted_byte = (uint64_t)lookup_table_buffer[i] << (8 * (i % 8));
//   current_number |= shifted_byte;
//   }

//   return lookup_table;
// }
