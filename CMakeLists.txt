#
#   module  : CMakeLists.txt
#   version : 1.20
#   date    : 01/23/24
#
cmake_minimum_required(VERSION 3.0)
project(Joy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  option(RUN_TESTS "Run standard tests" ON)
else()
  option(RUN_TESTS "Run standard tests" OFF)
endif()
find_package(BISON)
find_package(FLEX)
BISON_TARGET(MyParser ${CMAKE_SOURCE_DIR}/pars.y ${CMAKE_SOURCE_DIR}/pars.c
	     DEFINES_FILE ${CMAKE_SOURCE_DIR}/pars.h)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexr.l ${CMAKE_SOURCE_DIR}/lexr.c
	      COMPILE_FLAGS "--wincompat")
else()
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexr.l ${CMAKE_SOURCE_DIR}/lexr.c)
endif()
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
	       scan.c repl.c modl.c ylex.c util.c exec.c eval.c xerr.c otab.c
	       prog.c writ.c read.c save.c parm.c arty.c)
add_definitions(-DLINK="\\"${CMAKE_EXE_LINKER_FLAGS}\\"")
add_definitions(-DVERS="BDW ${CMAKE_BUILD_TYPE} ${CMAKE_PROJECT_VERSION}")
#
#    MSVC: cmake --build . --config Release
#
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_VERBOSE_MAKEFILE ON)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCOPYRIGHT -DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS")
  add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS}\\"")
  target_link_libraries(joy bdwgc/Release/gc)
  include_directories(bdwgc/include)
  add_subdirectory(bdwgc)
else()
  add_dependencies(joy always)
  add_custom_target(always
		    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		    COMMAND sh tabl.sh .
		    COMMAND sh prim.sh .)
  set(CF "-DCOPYRIGHT -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CF}")
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_RELEASE}\\"")
  else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CF} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_DEBUG}\\"")
  endif()
  target_link_libraries(joy m gc)
  if(RUN_TESTS)
    add_subdirectory(lib)
    add_subdirectory(test)
    add_subdirectory(test2)
  endif()
endif()
