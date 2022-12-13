cmake_minimum_required(VERSION 3.22)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project(hex C)

add_library(hex OBJECT)

set_target_properties(
  hex
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE 1
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
)

add_library(hex_static STATIC $<TARGET_OBJECTS:hex>)

set_target_properties(
  hex_static
  PROPERTIES
  OUTPUT_NAME hex
)

install(TARGETS hex_shared hex_static)

install(FILES include/hex.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()
