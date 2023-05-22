#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/hex.h"

#define test_decode_length(string, expected) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = 0; \
    int err = hex_decode((utf8_t *) string, string_len, NULL, &buffer_len); \
    assert(err == 0); \
    assert(buffer_len == expected); \
  };

int
main () {
  test_decode_length("61", 1);
  test_decode_length("6162", 2);
  test_decode_length("616263", 3);
  test_decode_length("61626364", 4);
  test_decode_length("6162636465", 5);
}
