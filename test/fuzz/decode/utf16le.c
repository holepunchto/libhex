#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/hex.h"

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Reinterpret the raw bytes as a sequence of UTF-16 code units.
  size_t units = size / sizeof(utf16_t);
  utf16_t *string = units > 0 ? malloc(units * sizeof(utf16_t)) : NULL;

  if (string != NULL) memcpy(string, data, units * sizeof(utf16_t));

  size_t buffer_len = units / 2;
  uint8_t *buffer = buffer_len > 0 ? malloc(buffer_len) : NULL;

  int err = hex_decode_utf16le(string, units, buffer, &buffer_len);

  if (err == 0) {
    assert(buffer_len == units / 2);

    if (buffer_len > 0) {
      // Re-encode the decoded bytes; the result must decode back identically.
      size_t reencoded_len = buffer_len * 2;
      utf16_t *reencoded = malloc(reencoded_len * sizeof(utf16_t));

      err = hex_encode_utf16le(buffer, buffer_len, reencoded, &reencoded_len);

      assert(err == 0);
      assert(reencoded_len == buffer_len * 2);

      size_t roundtrip_len = buffer_len;
      uint8_t *roundtrip = malloc(roundtrip_len);

      err = hex_decode_utf16le(reencoded, reencoded_len, roundtrip, &roundtrip_len);

      assert(err == 0);
      assert(roundtrip_len == buffer_len);
      assert(memcmp(roundtrip, buffer, buffer_len) == 0);

      free(roundtrip);
      free(reencoded);
    }
  }

  free(buffer);
  free(string);

  return 0;
}
