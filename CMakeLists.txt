cmake_minimum_required(VERSION 3.10)

project(ImageCompression)

set(SOURCES
  src/Decoder.cpp
  src/Encoder.cpp
  src/main.cpp
)

option(ASAN "Enable address sanitiser" OFF)

if(ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

option(UBSAN "Enable undefined behaviour sanitiser" OFF)

if(UBSAN)
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(ImageCompression ${SOURCES} )
