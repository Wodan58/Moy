#
#	Makefile for MOY executables
#

#
#  OLD VERSION, -o
#
macro(exe1 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -o ${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ${src}1.c ../initsym.c ../node.c ../memory.c ../error.c
	       ../utils1.c ../${FLEX_MyScanner_OUTPUTS} ../joy.c ../scan.c
	       ../print.c)
target_link_libraries(${src}1 gc-lib)
endmacro(exe1)

#
#  NEW VERSION, -c
#
macro(exe2 src)
add_custom_command(OUTPUT ${src}2.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -c ${src}.joy | clang-format >${src}2.c)
add_executable(${src}2 ${src}2.c ../memory1.c ../error.c ../factor.c
	       ../${FLEX_MyScanner_OUTPUTS} ../joy.c ../scan.c)
target_link_libraries(${src}2 gc-lib)
endmacro(exe2)

#
#  NEW VERSION, -c, MINIMAL
#
macro(exe3 src)
add_custom_command(OUTPUT ${src}3.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -c ${src}.joy | clang-format >${src}3.c)
add_executable(${src}3 ${src}3.c ../memory1.c ../error.c)
target_link_libraries(${src}3 gc-lib)
endmacro(exe3)

exe3(fib)
exe3(gcd)
exe3(test)
#exe1(jp-joytst)
#exe1(flatjoy)
exe3(jp-reprodtst)
exe3(modtst)
exe3(jp-nestrec)
exe3(laztst)
#exe1(joytut)
exe3(jp-church)
#exe1(grmtst)
exe3(grmtst)
exe3(mtrtst)
exe3(reptst)
exe3(tutorial)
exe3(symtst)
exe3(plgtst)
#exe1(lsptst)
