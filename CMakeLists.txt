#
#   module  : CMakeLists.txt
#   version : 1.23
#   date    : 03/26/24
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
		arty.c eval.c exec.c modl.c otab.c parm.c prog.c read.c repl.c
		save.c scan.c util.c writ.c xerr.c ylex.c)
add_definitions(-DLINK="\\"${CMAKE_EXE_LINKER_FLAGS}\\"")
add_definitions(-DVERS="${CMAKE_BUILD_TYPE} ${CMAKE_PROJECT_VERSION}")
#
#	MSVC: cmake --build . --config Release
#
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_VERBOSE_MAKEFILE ON)
  option(BUILD_SHARED_LIBS OFF)
  option(BUILD_TESTING OFF)
  option(build_cord OFF)
  option(enable_docs OFF)
  option(enable_threads OFF)
  option(enable_parallel_mark OFF)
  option(enable_thread_local_alloc OFF)
  option(enable_threads_discovery OFF)
  option(enable_throw_bad_alloc_library OFF)
  option(enable_gcj_support OFF)
  option(enable_java_finalization OFF)
  option(enable_atomic_uncollectable OFF)
  option(enable_disclaim OFF)
  option(enable_munmap OFF)
  option(enable_dynamic_loading OFF)
  option(enable_register_main_static_data OFF)
  option(enable_handle_fork OFF)
  option(install_headers OFF)
  option(disable_gc_debug ON)
  option(disable_single_obj_compilation ON)
  option(disable_handle_fork ON)
  option(without_libatomic_ops ON)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGC_NOT_DLL -D_CRT_SECURE_NO_DEPRECATE")
  add_definitions(-D__STDC_VERSION__=199901 -DCOMP="\\"${CMAKE_C_FLAGS}\\"")
  target_link_libraries(joy bdwgc/Release/gc)
  include_directories(bdwgc/include)
  add_subdirectory(bdwgc)
else()
  add_dependencies(joy always)
  add_custom_target(always
		    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		    COMMAND sh tabl.sh .
		    COMMAND sh prim.sh .)
  set(CF "-Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CF}")
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_RELEASE}\\"")
  else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CF} -g -O0 --coverage -fprofile-arcs -ftest-coverage")	# debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_DEBUG}\\"")
  endif()
  target_link_libraries(joy m gc)
  if(RUN_TESTS)
    add_subdirectory(test1)
    add_subdirectory(test2)
    add_subdirectory(lib)
  endif()
endif()
