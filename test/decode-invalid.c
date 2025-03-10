#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/hex.h"

#define test_decode_invalid(string) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = string_len; \
    uint8_t buffer[buffer_len]; \
    int err = hex_decode_utf8((utf8_t *) string, string_len, buffer, &buffer_len); \
    assert(err != 0); \
  };

int
main() {
  test_decode_invalid("v");
}
