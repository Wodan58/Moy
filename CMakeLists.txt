#
#   module  : CMakeLists.txt
#   version : 1.13
#   date    : 05/13/20
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
add_subdirectory(bdwgc)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} yylex.c compile.c
               initsym.c interp.c optable.c outfile.c print.c symbol.c
               utils.c dict.c memory.c node.c)
if(WIN32)
target_link_libraries(joy gc-lib)
else()
target_link_libraries(joy gc-lib m)
endif()
add_dependencies(joy always)
add_custom_target(always
		  COMMAND sh banner.sh ${PROJECT_NAME} ${PROJECT_VERSION}
		  COMMAND sh parse.sh bison -doparse.c parse.y
		  COMMAND sh table.sh
		  COMMAND sh prims.sh
		  COMMAND sh trans.sh
		 )
if(WIN32)
else()
add_subdirectory(lib)
add_subdirectory(test)
endif()
