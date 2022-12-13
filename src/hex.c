#include <math.h>
#include <stdio.h>

#include "../include/hex.h"

static const char hex_alphabet[16] = "0123456789abcdef";

static const char hex_inverse_alphabet[256] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

int
hex_encode (const char *buffer, size_t buffer_len, char *string, size_t *string_len) {
  size_t len = buffer_len * 2;

  if (string == NULL) {
    *string_len = len;
    return 0;
  }

  if (*string_len < len + 1) return -1;

  *string_len = len;

  size_t k = 0;

  for (size_t i = 0, n = buffer_len; i < n; i++) {
    string[k++] = hex_alphabet[buffer[i] >> 4];
    string[k++] = hex_alphabet[buffer[i] & 0x0f];
  }

  string[k] = '\0';

  return 0;
}

int
hex_decode (const char *string, size_t string_len, char *buffer, size_t *buffer_len) {
  size_t len = string_len >> 1;

  if (buffer == NULL) {
    *buffer_len = len;
    return 0;
  }

  if (*buffer_len < len + 1) return -1;

  *buffer_len = len;

  size_t k = 0;

  for (size_t i = 0, n = string_len; i < n; i += 2) {
    char chunk[2];

    for (size_t j = 0; j < 2; j++) {
      chunk[j] = i + j < n ? hex_inverse_alphabet[string[i + j]] : 0;

      if (chunk[j] == -1) return -1;
    }

    buffer[k++] = (chunk[0] << 4) | chunk[1];
  }

  return 0;
}
