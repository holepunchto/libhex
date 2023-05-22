#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/hex.h"

#define test_decode(string, expected) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = string_len; \
    uint8_t buffer[buffer_len]; \
    int err = hex_decode((utf8_t *) string, string_len, buffer, &buffer_len); \
    assert(err == 0); \
    assert(buffer_len == strlen(expected)); \
    assert(strncmp((char *) buffer, expected, buffer_len) == 0); \
  };

int
main () {
  test_decode("61", "a");
  test_decode("6162", "ab");
  test_decode("616263", "abc");
  test_decode("61626364", "abcd");
  test_decode("6162636465", "abcde");
}
