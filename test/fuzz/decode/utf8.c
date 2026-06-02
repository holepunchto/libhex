#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/hex.h"

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Decoded output is at most half the input length.
  size_t buffer_len = size / 2;
  uint8_t *buffer = buffer_len > 0 ? malloc(buffer_len) : NULL;

  int err = hex_decode_utf8((const utf8_t *) data, size, buffer, &buffer_len);

  if (err == 0) {
    assert(buffer_len == size / 2);

    if (buffer_len > 0) {
      // Re-encode the decoded bytes; the result must decode back identically.
      size_t string_len = buffer_len * 2;
      utf8_t *string = malloc(string_len);

      err = hex_encode_utf8(buffer, buffer_len, string, &string_len);

      assert(err == 0);
      assert(string_len == buffer_len * 2);

      size_t roundtrip_len = buffer_len;
      uint8_t *roundtrip = malloc(roundtrip_len);

      err = hex_decode_utf8(string, string_len, roundtrip, &roundtrip_len);

      assert(err == 0);
      assert(roundtrip_len == buffer_len);
      assert(memcmp(roundtrip, buffer, buffer_len) == 0);

      free(roundtrip);
      free(string);
    }
  }

  free(buffer);

  return 0;
}
