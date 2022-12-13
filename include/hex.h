#ifndef HEX_H
#define HEX_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int
hex_encode (const char *buffer, size_t buffer_len, char *string, size_t *string_len);

int
hex_decode (const char *string, size_t string_len, char *buffer, size_t *buffer_len);

#ifdef __cplusplus
}
#endif

#endif // HEX_H
