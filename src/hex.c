#include <stdint.h>
#include <utf.h>

#include "../include/hex.h"

extern int
hex_encode (const uint8_t *buffer, size_t buffer_len, utf8_t *string, size_t *string_len);

extern int
hex_decode (const utf8_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len);
