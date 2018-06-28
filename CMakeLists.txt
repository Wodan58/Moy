#
#   module  : cmakelists.txt
#   version : 1.2
#   date    : 06/28/18
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.0)
set(CMAKE_BUILD_TYPE Release)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
find_package(FLEX)
FLEX_TARGET(MyScanner lexer.l lexer.c)
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
include_directories(. src bdwgc/include)
add_executable(moy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
	       arity.c aritysym.c compile.c history.c initmem.c initsym.c
	       interp.c joy.c listing.c node.c optable.c outfile.c print.c
	       scan.c symbol.c utils.c dict.c)
target_link_libraries(moy gc-lib)
add_dependencies(moy always)
add_custom_target(always
		  COMMAND sh banner.sh ${PROJECT_NAME} ${PROJECT_VERSION}
		  COMMAND sh parse.sh bison -doparse.c parse.y
		  COMMAND sh table.sh
		  COMMAND sh prims.sh
		  COMMAND sh trans.sh)
add_subdirectory(bdwgc)
add_subdirectory(test)
