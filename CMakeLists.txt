#
#	Makefile for MOY
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.0)
set(CMAKE_BUILD_TYPE Release)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
add_custom_target(parse-h DEPENDS parse.h)
add_custom_command(OUTPUT parse.h
		   COMMAND ${BISON_EXECUTABLE} -doparse.c parse.y
		   DEPENDS parse.y)
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
include_directories(. SRC bdwgc/include)
add_subdirectory(bdwgc)
add_executable(moy ${BISON_MyParser_OUTPUTS}
		compile.c interp.c listing.c main.c outfile.c history.c)
target_link_libraries(moy joy gc-lib)
add_subdirectory(SRC)
add_dependencies(joy parse-h)
add_subdirectory(LIB)
