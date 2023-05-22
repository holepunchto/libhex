#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/hex.h"

#define test_encode(buffer, expected) \
  { \
    size_t buffer_len = strlen(buffer); \
    size_t string_len = buffer_len * 2 + 1; \
    char string[string_len]; \
    int err = hex_encode((uint8_t *) buffer, buffer_len, (utf8_t *) string, &string_len); \
    assert(err == 0); \
    assert(string_len == strlen(expected)); \
    assert(strncmp(string, expected, string_len) == 0); \
  };

int
main () {
  test_encode("a", "61");
  test_encode("ab", "6162");
  test_encode("abc", "616263");
  test_encode("abcd", "61626364");
  test_encode("abcde", "6162636465");
}
