#
#   module  : CMakeLists.txt
#   version : 1.1
#   date    : 06/26/18
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.0)
set(CMAKE_BUILD_TYPE Release)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
find_package(FLEX)
if(WIN32)
FLEX_TARGET(MyScanner lexer.l lexer.c COMPILE_FLAGS --wincompat)
else()
FLEX_TARGET(MyScanner lexer.l lexer.c)
endif()
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
include_directories(. src bdwgc/include)
add_executable(moy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
	       arity.c aritysym.c compile.c history.c initmem.c initsym.c
	       interp.c joy.c listing.c node.c optable.c outfile.c print.c
	       scan.c symbol.c utils.c)
add_dependencies(moy always)
add_custom_target(always
		  COMMAND sh parse.sh
		  COMMAND sh table.sh)
target_link_libraries(moy joy gc-lib)
add_subdirectory(bdwgc)
add_subdirectory(src)
add_dependencies(joy always)
# add_subdirectory(test)
