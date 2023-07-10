#
#   module  : CMakeLists.txt
#   version : 1.1
#   date    : 07/10/23
#
cmake_minimum_required(VERSION 3.4)
project(Moy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
set(CMAKE_BUILD_TYPE "Debug")
endif()
if(WIN32)
option(WINDOWS "Use _MSC_VER compiler" ON)
endif()
option(REAL_BDW "Use BDW garbage collector" ON)
option(RUN_TESTS "Run standard tests" ON)
find_package(BISON)
find_package(FLEX)
BISON_TARGET(MyParser ${CMAKE_SOURCE_DIR}/pars.y ${CMAKE_SOURCE_DIR}/pars.c
	     DEFINES_FILE ${CMAKE_SOURCE_DIR}/pars.h)
if(WINDOWS)
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexr.l ${CMAKE_SOURCE_DIR}/lexr.c
	      COMPILE_FLAGS "--wincompat")
  add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
else()
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexr.l ${CMAKE_SOURCE_DIR}/lexr.c)
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
  endif()
endif()
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
#add_definitions(-ansi -pedantic "-Dkh_inline=""" -DULLONG_MAX=ULONG_MAX)
add_definitions(-DGC_BDW -DTRACING -DJVERSION="${CMAKE_BUILD_TYPE} ${CMAKE_PROJECT_VERSION}")
add_executable(joy arty.c comp.c dtim.c eval.c ${FLEX_MyScanner_OUTPUTS} list.c
                   main.c manl.c modl.c parm.c ${BISON_MyParser_OUTPUTS} prog.c
                   read.c repl.c save.c scan.c syml.c undo.c util.c writ.c)
if(WINDOWS)
target_link_libraries(joy gc-lib)
include_directories(bdwgc/include)
add_dependencies(joy always)
add_custom_target(always
		  COMMAND sh ${CMAKE_SOURCE_DIR}/tabl.sh ${CMAKE_SOURCE_DIR}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/prim.sh ${CMAKE_SOURCE_DIR}
		 )
add_subdirectory(bdwgc)
else()
target_link_libraries(joy m gc)
add_dependencies(joy always)
add_custom_target(always
		  COMMAND sh ${CMAKE_SOURCE_DIR}/tabl.sh ${CMAKE_SOURCE_DIR}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/prim.sh ${CMAKE_SOURCE_DIR}
		 )
if(RUN_TESTS)
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(test2)
endif()
endif()
