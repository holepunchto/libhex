#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/hex.h"

#define test_decode_invalid_utf8(string) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = string_len; \
    uint8_t buffer[buffer_len]; \
    int err = hex_decode_utf8((utf8_t *) string, string_len, buffer, &buffer_len); \
    assert(err != 0); \
  };

#define test_decode_invalid_utf16le(units, n) \
  { \
    size_t buffer_len = n; \
    uint8_t buffer[buffer_len]; \
    int err = hex_decode_utf16le(units, n, buffer, &buffer_len); \
    assert(err != 0); \
  };

int
main() {
  test_decode_invalid_utf8("v");

  // Odd-length input must be rejected (previously overflowed the buffer).
  test_decode_invalid_utf8("abc");

  utf16_t odd[3] = {'a', 'b', 'c'};
  test_decode_invalid_utf16le(odd, 3);

  // UTF-16 code units > 0xff must be rejected (previously read past the
  // 256-entry lookup table).
  utf16_t high[2] = {'6', 0x20ac};
  test_decode_invalid_utf16le(high, 2);
}
