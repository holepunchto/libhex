cmake_minimum_required(VERSION 3.22)

project(hex C)

if(NOT TARGET utf)
  add_subdirectory(vendor/libutf EXCLUDE_FROM_ALL)
endif()

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
    $<TARGET_PROPERTY:utf,INTERFACE_INCLUDE_DIRECTORIES>
)

add_library(hex_shared SHARED)

set_target_properties(
  hex_shared
  PROPERTIES
  OUTPUT_NAME hex
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  hex_shared
  PUBLIC
    hex
)

add_library(hex_static STATIC $<TARGET_OBJECTS:hex>)

set_target_properties(
  hex_static
  PROPERTIES
  OUTPUT_NAME hex
  PREFIX lib
)

target_link_libraries(
  hex_static
  PUBLIC
    hex
)

install(TARGETS hex_shared hex_static)

install(FILES include/hex.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
