#
#  Makefile for MOY
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.01)
set(BM false)
set(BMX false)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
add_custom_target(parse_h DEPENDS parse.h)
add_custom_command(OUTPUT parse.h
		   COMMAND ${BISON_EXECUTABLE} -doparse.c parse.y
		   DEPENDS parse.y)
include_directories(.)
if(BMX)
add_definitions(-DARITY)
endif(BMX)
add_definitions(-DBIT_32 -Ofast -mno-red-zone -fno-omit-frame-pointer
		-Wall -Wextra -Werror -Wno-missing-field-initializers
		-Wno-sign-compare -fno-align-functions -fno-align-loops
		-fno-align-jumps -fno-align-labels -fno-exceptions
		-fno-builtin -fno-asynchronous-unwind-tables)
add_executable(moy ${BISON_MyParser_OUTPUTS} main1.c compile.c eval.c parse.c
	       print.c)
target_link_libraries(moy joy gc-lib)
add_subdirectory(src)
add_dependencies(joy parse_h)
add_subdirectory(bdwgc)
if(BM)
macro(exe src)
add_custom_target(${src}.c DEPENDS ${src}.joy)
add_custom_command(OUTPUT ${src}.c
		   COMMAND moy -c ${src}.joy | clang-format >${src}.c
		   DEPENDS moy ${src}.joy)
add_executable(${src} main2.c ${src}.c)
target_link_libraries(${src} joy gc-lib)
endmacro(exe)
exe(fib)
else(BM)
add_subdirectory(lib)
endif(BM)
