add_test_executables(
  decode.c
  decode-invalid.c
  decode-length.c
  encode.c
  encode-length.c
  LINK
    hex::<TYPE>
)

add_subdirectory(fuzz)
