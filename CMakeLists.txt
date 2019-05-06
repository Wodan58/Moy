#
#   module  : cmakelists.txt
#   version : 1.5
#   date    : 12/30/18
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.0)
set(CMAKE_BUILD_TYPE Debug)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
find_package(FLEX)
if(WIN32)
FLEX_TARGET(MyScanner lexer.l lexer.c COMPILE_FLAGS --wincompat)
else()
FLEX_TARGET(MyScanner lexer.l lexer.c)
endif()
add_definitions(-DDEBUG -DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
if(WIN32)
else()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
endif()
include_directories(. src bdwgc/include)
add_executable(moy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
	       compile.c initmem.c initsym.c interp.c joy.c node.c optable.c
	       outfile.c print.c scan.c symbol.c utils.c dict.c memory.c)
target_link_libraries(moy gc-lib)
add_dependencies(moy always)
add_custom_target(always
		  COMMAND sh banner.sh ${PROJECT_NAME} ${PROJECT_VERSION}
		  COMMAND sh parse.sh bison -doparse.c parse.y
		  COMMAND sh table.sh
		  COMMAND sh prims.sh
		  COMMAND sh trans.sh
		 )
add_subdirectory(bdwgc)
add_subdirectory(test)
