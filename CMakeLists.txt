#
#   module  : CMakeLists.txt
#   version : 1.30
#   date    : 09/24/24
#
cmake_minimum_required(VERSION 3.5)
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
		arty.c eval.c exec.c module.c otab.c parm.c prog.c read.c repl.c
		save.c scan.c util.c writ.c error.c ylex.c print.c)
add_definitions(-DLINK="\\"${CMAKE_EXE_LINKER_FLAGS}\\"")
add_definitions(-DVERS="${CMAKE_BUILD_TYPE} ${CMAKE_PROJECT_VERSION}")
#
#	MSVC: cmake --build . --config Release
#
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_VERBOSE_MAKEFILE ON)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGC_NOT_DLL -D_CRT_SECURE_NO_DEPRECATE")
  add_definitions(-D__STDC_VERSION__=199901 -DCOMP="\\"${CMAKE_C_FLAGS}\\"")
  target_link_libraries(joy ../../joy1/gc-8.2.8/build/Release/gc)
else()
  add_dependencies(joy always)
  add_custom_target(always
		    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		    COMMAND sh prim.sh .
		    COMMAND sh tabl.sh .)
  set(CF "-Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-result")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CF}")
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_RELEASE}\\"")
  else()
    set(CMAKE_C_FLAGS_DEBUG	# debug, enabling coverage
  "${CMAKE_C_FLAGS_DEBUG} ${CF} -O3 --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_DEBUG}\\"")
  endif()
  target_link_libraries(joy m gc)
  if(RUN_TESTS)
    add_subdirectory(test1)
    add_subdirectory(test2)
    add_subdirectory(lib)
  endif()
endif()
