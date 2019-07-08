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
	       ../utils1.c ../yylex1.c ../print.c)
target_link_libraries(${src}1 gc-lib)
endmacro(exe1)

#
#  NEW VERSION, -c
#
macro(exe2 src)
add_custom_command(OUTPUT ${src}2.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -c ${src}.joy | clang-format >${src}2.c)
add_executable(${src}2 ${src}2.c ../memory.c ../error.c ../factor.c ../yylex1.c)
target_link_libraries(${src}2 gc-lib)
endmacro(exe2)

#
#  NEW VERSION, -c, MINIMAL
#
macro(exe3 src)
add_custom_command(OUTPUT ${src}3.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -c ${src}.joy | clang-format >${src}3.c)
add_executable(${src}3 ${src}3.c ../memory.c ../error.c)
target_link_libraries(${src}3 gc-lib)
endmacro(exe3)

#
#  OLDER VERSION, -r
#
macro(exe4 src)
add_custom_command(OUTPUT ${src}4.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -r ${src}.joy | clang-format >${src}4.c)
add_executable(${src}4 ${src}4.c ../initsym.c ../node1.c ../memory.c ../error.c
	       ../print.c ../yylex1.c ../utils1.c)
target_link_libraries(${src}4 gc-lib)
endmacro(exe4)

#
#  OLDER VERSION, -r, MINIMAL
#
macro(exe5 src)
add_custom_command(OUTPUT ${src}5.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -r ${src}.joy | clang-format >${src}5.c)
add_executable(${src}5 ${src}5.c ../initsym1.c ../node1.c ../memory.c ../error.c
	       ../print.c)
target_link_libraries(${src}5 gc-lib)
endmacro(exe5)

add_executable(fib fib.c)
exe1(fib)
exe3(fib)
exe5(fib)
exe1(gcd)
exe3(gcd)
exe5(gcd)
exe1(test)
exe3(test)
exe5(test)
exe1(jp-joytst)
#exe3(jp-joytst)	body, opcase not supported
exe5(jp-joytst)
exe1(flatjoy)
exe3(flatjoy)
exe5(flatjoy)
exe1(jp-reprodtst)
exe3(jp-reprodtst)
exe5(jp-reprodtst)
exe1(modtst)
exe3(modtst)
exe5(modtst)
exe1(jp-nestrec)
exe3(jp-nestrec)
exe5(jp-nestrec)
exe1(laztst)
exe3(laztst)
exe5(laztst)
exe1(joytut)
exe2(joytut)
exe4(joytut)
exe1(jp-church)
exe3(jp-church)
exe5(jp-church)
exe1(grmtst)
exe3(grmtst)
exe5(grmtst)
exe1(mtrtst)
exe3(mtrtst)
exe5(mtrtst)
exe1(reptst)
exe3(reptst)
exe5(reptst)
exe1(tutorial)
exe3(tutorial)
exe5(tutorial)
exe1(symtst)
exe3(symtst)
exe5(symtst)
exe1(plgtst)
exe3(plgtst)
exe5(plgtst)
exe1(lsptst)
exe2(lsptst)
exe4(lsptst)
