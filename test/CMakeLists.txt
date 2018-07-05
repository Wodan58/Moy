#
#	Makefile for MOY executables
#
macro(exe1 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -c ${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ${src}1.c ../${FLEX_MyScanner_OUTPUTS} ../error.c
		../initsym.c ../interp1.c ../joy.c ../node.c ../optable.c
		../print.c ../scan.c ../symbol.c ../utils1.c ../memory.c)
target_link_libraries(${src}1 gc-lib)
endmacro(exe1)

#
#  NEW_VERSION
#
macro(exe2 src)
add_custom_command(OUTPUT ${src}2.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -c ${src}.joy | clang-format >${src}2.c)
add_executable(${src}2 ${src}2.c ../${FLEX_MyScanner_OUTPUTS} ../factor.c
		../scan.c ../memory1.c ../joy.c ../error.c)
target_link_libraries(${src}2 gc-lib)
endmacro(exe2)

exe2(tutorial)
exe2(fib)
exe2(modtst)
exe2(gcd)
exe2(test)
exe2(jp-reprodtst)
exe2(jp-joytst)
exe2(flatjoy)
exe2(lsptst)
exe2(joytut)
exe2(laztst)
exe2(jp-nestrec)
exe2(jp-church)
exe2(reptst)
exe2(mtrtst)
exe2(symtst)
exe2(grmtst)
exe2(plgtst)

# exe1(tutorial)
# exe1(fib)
# exe1(gcd)
# exe1(test)
# exe1(modtst)
# exe1(flatjoy)
# exe1(jp-reprodtst)
# exe1(jp-joytst)
# exe1(lsptst)
# exe1(joytut)
# exe1(laztst)
# exe1(reptst)
# exe1(jp-nestrec)
# exe1(jp-church)
# exe1(mtrtst)
# exe1(symtst)
# exe1(grmtst)
# exe1(plgtst)
