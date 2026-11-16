if(TARGET hex_shared)
  set(library hex::shared)
else()
  set(library hex::static)
endif()

add_test_executables(
  decode.c
  decode-invalid.c
  decode-length.c
  encode.c
  encode-length.c
  LINK
    ${library}
)

add_subdirectory(fuzz)
