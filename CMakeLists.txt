#
#  Makefile for MOY
#
cmake_minimum_required(VERSION 2.8.9)
project(Moy)

set(BIT_32 ON)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser parse.y ${CMAKE_CURRENT_BINARY_DIR}/parse.c)
FLEX_TARGET(MyScanner lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,0x100000")

add_definitions(-I../bdwgc/include -O3 -Wall -Wextra -Werror -Wno-unused-function)

if(BIT_32)
  add_definitions(-DBIT_32)
else()
  add_definitions(-Wno-format)
endif()

add_executable(moy interp1.c scan1.c utils1.c main1.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS} getsym.c joy.c symbol.c initmem.c)

add_library(gc STATIC IMPORTED)
set_target_properties(gc PROPERTIES IMPORTED_LOCATION ../bdwgc/libgc-lib.a)
target_link_libraries(moy gc)
