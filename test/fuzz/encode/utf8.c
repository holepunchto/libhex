#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/hex.h"

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Each input byte expands to exactly 2 hex characters.
  size_t string_len = size * 2;
  utf8_t *string = string_len > 0 ? malloc(string_len) : NULL;

  int err = hex_encode_utf8(data, size, string, &string_len);

  assert(err == 0);
  assert(string_len == size * 2);

  if (size > 0) {
    size_t buffer_len = size;
    uint8_t *buffer = malloc(buffer_len);

    err = hex_decode_utf8(string, string_len, buffer, &buffer_len);

    assert(err == 0);
    assert(buffer_len == size);
    assert(memcmp(buffer, data, size) == 0);

    free(buffer);
  }

  free(string);

  return 0;
}
