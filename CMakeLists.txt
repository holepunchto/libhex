cmake_minimum_required(VERSION 3.22)

project(hex C)

add_library(hex OBJECT)

set_target_properties(
  hex
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
)

target_sources(
  hex
  INTERFACE
    include/hex.h
  PRIVATE
    src/hex.c
)

target_include_directories(
  hex
  PUBLIC
    include
)

add_library(hex_shared SHARED $<TARGET_OBJECTS:hex>)

set_target_properties(
  hex_shared
  PROPERTIES
  OUTPUT_NAME hex
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

add_library(hex_static STATIC $<TARGET_OBJECTS:hex>)

set_target_properties(
  hex_static
  PROPERTIES
  OUTPUT_NAME hex
  PREFIX lib
)

install(TARGETS hex_shared hex_static)

install(FILES include/hex.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()
