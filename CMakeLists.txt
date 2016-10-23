#
#  Makefile for MOY
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.01)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
add_custom_target(parse_h DEPENDS parse.h)
add_custom_command(OUTPUT parse.h
		   COMMAND ${BISON_EXECUTABLE} -doparse.c parse.y
		   DEPENDS parse.y)
include_directories(.)
add_definitions(-DBIT_32 -Ofast -mno-red-zone -fno-omit-frame-pointer
		-Wall -Wextra -Werror -Wno-missing-field-initializers
		-Wno-sign-compare -fno-align-functions -fno-align-loops
		-fno-align-jumps -fno-align-labels -fno-exceptions
		-fno-builtin -fno-asynchronous-unwind-tables)
add_executable(moy ${BISON_MyParser_OUTPUTS} main1.c compile.c eval.c parse.c
	       print.c)
target_link_libraries(moy joy /usr/local/lib/libgc-lib.a)
add_subdirectory(src)
add_dependencies(joy parse_h)
add_subdirectory(lib)
