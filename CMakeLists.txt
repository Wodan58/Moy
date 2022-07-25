#
#   module  : CMakeLists.txt
#   version : 1.27
#   date    : 07/25/22
#
cmake_minimum_required(VERSION 3.4)
project(Moy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
endif()
if(WIN32)
option(WINDOWS "Use _MSC_VER compiler" ON)
endif()
option(REAL_BDW "Use BDW garbage collector" OFF)
option(RUN_TESTS "Run standard tests" ON)
find_package(BISON)
find_package(FLEX)
BISON_TARGET(MyParser ${CMAKE_SOURCE_DIR}/parse.y ${CMAKE_SOURCE_DIR}/parse.c
	     DEFINES_FILE ${CMAKE_SOURCE_DIR}/parse.h)
if(WINDOWS)
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexer.l ${CMAKE_SOURCE_DIR}/lexer.c
	      COMPILE_FLAGS "--wincompat")
  add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
else()
  FLEX_TARGET(MyScanner ${CMAKE_SOURCE_DIR}/lexer.l ${CMAKE_SOURCE_DIR}/lexer.c)
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -I. -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
  endif()
endif()
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
if(REAL_BDW)
  add_definitions(-DGC_BDW
		  -DJVERSION="BDW ${CMAKE_BUILD_TYPE} ${PROJECT_VERSION}")
  include_directories(bdwgc/include src .)
  add_executable(joy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
		 joy.c compile.c initsym.c interp.c optable.c outfile.c print.c
		 module.c dict.c node.c scan.c tmpfile.c utils.c)
  if(WINDOWS)
    target_link_libraries(joy gc-lib ws2_32)
  else()
    target_link_libraries(joy gc-lib m)
  endif()
  add_subdirectory(bdwgc)
else()
  add_definitions(-DJVERSION="MINGC ${CMAKE_BUILD_TYPE} ${PROJECT_VERSION}")
  include_directories(src .)
  add_executable(joy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
		 joy.c compile.c initsym.c interp.c optable.c outfile.c print.c
		 module.c dict.c node.c scan.c tmpfile.c utils.c gc.c)
  if(WINDOWS)
    target_link_libraries(joy ws2_32)
  else()
    target_link_libraries(joy m)
  endif()
endif()
add_dependencies(joy always)
if(WINDOWS)
  add_custom_target(always
		    COMMAND sh ${CMAKE_SOURCE_DIR}/table.sh ${CMAKE_SOURCE_DIR}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/prims.sh ${CMAKE_SOURCE_DIR}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/trans.sh ${CMAKE_SOURCE_DIR}
		   )
else()
  add_custom_target(always
		    COMMAND sh ${CMAKE_SOURCE_DIR}/banner.sh ${PROJECT_NAME} ${PROJECT_VERSION}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/table.sh ${CMAKE_SOURCE_DIR}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/prims.sh ${CMAKE_SOURCE_DIR}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/trans.sh ${CMAKE_SOURCE_DIR}
		   )
  if(RUN_TESTS)
#   add_subdirectory(lib)
    add_subdirectory(test)
    add_subdirectory(test2)
  endif()
endif()
