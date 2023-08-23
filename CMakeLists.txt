#
#   module  : CMakeLists.txt
#   version : 1.11
#   date    : 08/23/23
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()
option(RUN_TESTS "Run standard tests" OFF)
find_package(BISON)
find_package(FLEX)
BISON_TARGET(MyParser ${CMAKE_SOURCE_DIR}/pars.y ${CMAKE_SOURCE_DIR}/pars.c
	     DEFINES_FILE ${CMAKE_SOURCE_DIR}/pars.h)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexr.l ${CMAKE_SOURCE_DIR}/lexr.c
              COMPILE_FLAGS "--wincompat")
  add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
else()
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexr.l ${CMAKE_SOURCE_DIR}/lexr.c)
endif()
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
add_definitions(-DSYMBOLS -DCOPYRIGHT -DJVERSION="${CMAKE_BUILD_TYPE} ${CMAKE_PROJECT_VERSION}")
add_executable(joy arty.c comp.c dtim.c eval.c ${FLEX_MyScanner_OUTPUTS} main.c
                   manl.c modl.c parm.c ${BISON_MyParser_OUTPUTS} prog.c read.c
                   repl.c save.c scan.c undo.c util.c writ.c ylex.c)
add_dependencies(joy always)
add_custom_target(always
		  COMMAND sh ${CMAKE_SOURCE_DIR}/tabl.sh ${CMAKE_SOURCE_DIR}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/prim.sh ${CMAKE_SOURCE_DIR}
		 )
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_link_libraries(joy gc-lib)
  include_directories(bdwgc/include)
  add_subdirectory(bdwgc)
else()
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
  endif()
  target_link_libraries(joy m gc)
  if(RUN_TESTS)
    add_subdirectory(lib)
    add_subdirectory(test)
    add_subdirectory(test2)
  endif()
endif()
