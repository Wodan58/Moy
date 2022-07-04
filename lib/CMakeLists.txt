#
#   module  : CMakeLists.txt
#   version : 1.5
#   date    : 06/18/22
#
macro(exe9 src)
add_custom_target(${src}.out ALL
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		  COMMAND joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy 24 54 >${src}.out)
endmacro(exe9)

#
#	interpreter
#
exe9(fib)
exe9(gcd)
exe9(test)
exe9(flatjoy)
exe9(jp-reprodtst)
exe9(jp-nestrec)
exe9(laztst)
exe9(jp-church)
exe9(grmtst)
exe9(mtrtst)
exe9(reptst)
exe9(tutorial)
exe9(symtst)
exe9(plgtst)
exe9(jp-joytst)
exe9(modtst)

add_custom_target(test31.out ALL
		  DEPENDS joy
		  COMMAND cat ${CMAKE_SOURCE_DIR}/lib/tutinp.joy
			      ${CMAKE_SOURCE_DIR}/lib/tutinp.inp >t
		  COMMAND joy -v <t >test31.out)
add_custom_target(test32.out ALL
		  DEPENDS joy
		  COMMAND cat ${CMAKE_SOURCE_DIR}/lib/lsptst.joy
			      ${CMAKE_SOURCE_DIR}/lib/lsptst.inp >t
		  COMMAND joy -v <t >test32.out)

#
#	executables
#
if(REAL_BDW)
macro(exe8 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -c ${CMAKE_SOURCE_DIR}/lib/${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}/main.c ${src}1.c
		       ${CMAKE_SOURCE_DIR}/initsym.c
		       ${CMAKE_SOURCE_DIR}/node.c
		       ${CMAKE_SOURCE_DIR}/utils.c
		       ${FLEX_MyScanner_OUTPUTS} # yylex.c
		       ${CMAKE_SOURCE_DIR}/scan.c
		       ${CMAKE_SOURCE_DIR}/joy.c
		       ${CMAKE_SOURCE_DIR}/print.c
		       ${CMAKE_SOURCE_DIR}/runtime.c)
target_link_libraries(${src}1 gc-lib m)
endmacro(exe8)

macro(exe7 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -l ${CMAKE_SOURCE_DIR}/lib/${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}/main.c ${src}1.c
		       ${CMAKE_SOURCE_DIR}/initsym.c
		       ${CMAKE_SOURCE_DIR}/node.c
		       ${CMAKE_SOURCE_DIR}/utils.c
		       ${FLEX_MyScanner_OUTPUTS} # yylex.c
		       ${CMAKE_SOURCE_DIR}/scan.c
		       ${CMAKE_SOURCE_DIR}/joy.c
		       ${CMAKE_SOURCE_DIR}/print.c
		       ${CMAKE_SOURCE_DIR}/runtime.c)
target_link_libraries(${src}1 gc-lib m)
endmacro(exe7)
else()
macro(exe8 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -c ${CMAKE_SOURCE_DIR}/lib/${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}/main.c ${src}1.c
		       ${CMAKE_SOURCE_DIR}/initsym.c
		       ${CMAKE_SOURCE_DIR}/node.c
		       ${CMAKE_SOURCE_DIR}/utils.c
		       ${FLEX_MyScanner_OUTPUTS} # yylex.c
		       ${CMAKE_SOURCE_DIR}/scan.c
		       ${CMAKE_SOURCE_DIR}/joy.c
		       ${CMAKE_SOURCE_DIR}/print.c
		       ${CMAKE_SOURCE_DIR}/runtime.c
		       ${CMAKE_SOURCE_DIR}/gc.c)
target_link_libraries(${src}1 m)
endmacro(exe8)

macro(exe7 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -l ${CMAKE_SOURCE_DIR}/lib/${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}/main.c ${src}1.c
		       ${CMAKE_SOURCE_DIR}/initsym.c
		       ${CMAKE_SOURCE_DIR}/node.c
		       ${CMAKE_SOURCE_DIR}/utils.c
		       ${FLEX_MyScanner_OUTPUTS} # yylex.c
		       ${CMAKE_SOURCE_DIR}/scan.c
		       ${CMAKE_SOURCE_DIR}/joy.c
		       ${CMAKE_SOURCE_DIR}/print.c
		       ${CMAKE_SOURCE_DIR}/runtime.c
		       ${CMAKE_SOURCE_DIR}/gc.c)
target_link_libraries(${src}1 m)
endmacro(exe7)
endif()

exe8(fib)
exe8(gcd)
exe8(test)
exe8(jp-joytst)
exe8(flatjoy)
exe8(jp-reprodtst)
exe8(modtst)
exe8(jp-nestrec)
exe8(laztst)
exe8(tutinp)
exe8(jp-church)
exe8(grmtst)
exe8(mtrtst)
exe8(reptst)
exe8(tutorial)
exe8(symtst)
exe8(plgtst)
exe7(lsptst)
