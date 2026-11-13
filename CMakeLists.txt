cmake_minimum_required(VERSION 4.0)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-fuzz REQUIRED PATHS node_modules/cmake-fuzz)

project(hex C)

fetch_package("github:holepunchto/libutf")

get_property(shared GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)

add_library(hex OBJECT)

set_target_properties(
  hex
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ${shared}
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

if(shared)
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
endif()

add_library(hex_static STATIC)

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

install(TARGETS hex_static)

if(shared)
  install(TARGETS hex_shared)
endif()

install(FILES include/hex.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
