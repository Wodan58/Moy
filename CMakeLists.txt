#
#   module  : CMakeLists.txt
#   version : 1.7
#   date    : 07/08/19
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.0)
set(CMAKE_BUILD_TYPE Release)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
if(WIN32)
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
else()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
endif()
include_directories(. src bdwgc/include)
add_executable(moy main.c ${BISON_MyParser_OUTPUTS} yylex.c
	       compile.c initmem.c initsym.c interp.c node1.c optable.c
	       outfile.c print.c symbol.c utils.c dict.c memory.c)
target_link_libraries(moy gc-lib m)
add_dependencies(moy always)
add_custom_target(always
		  COMMAND sh banner.sh ${PROJECT_NAME} ${PROJECT_VERSION}
		  COMMAND sh parse.sh bison -doparse.c parse.y
		  COMMAND sh table.sh
		  COMMAND sh prims.sh
		  COMMAND sh trans.sh
		 )
add_subdirectory(bdwgc)
if(WIN32)
else()
add_subdirectory(test)
endif()
