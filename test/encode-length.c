#include <assert.h>
#include <string.h>

#include "../include/hex.h"

#define test_encode_length(buffer, expected) \
  { \
    size_t buffer_len = strlen(buffer); \
    size_t string_len = 0; \
    int err = hex_encode(buffer, buffer_len, NULL, &string_len); \
    assert(err == 0); \
    assert(string_len == expected); \
  };

int
main () {
  test_encode_length("a", 2);
  test_encode_length("ab", 4);
  test_encode_length("abc", 6);
  test_encode_length("abcd", 8);
  test_encode_length("abcde", 10);
}
