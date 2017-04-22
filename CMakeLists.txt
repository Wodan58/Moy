#
#	Makefile for MOY
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.01)
set(CMAKE_BUILD_TYPE Release)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
add_custom_target(parse-h DEPENDS parse.h)
add_custom_command(OUTPUT parse.h
		   COMMAND ${BISON_EXECUTABLE} -doparse.c parse.y
		   DEPENDS parse.y)
add_definitions(-DYYDEBUG=1)
include_directories(. src)
add_executable(moy ${BISON_MyParser_OUTPUTS}
		compile.c interp.c listing.c main.c outfile.c history.c)
target_link_libraries(moy joy /usr/local/lib/libgc-lib.a)
add_subdirectory(src)
add_dependencies(joy parse-h)
add_subdirectory(lib)
