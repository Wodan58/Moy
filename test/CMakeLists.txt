#
#	Makefile for MOY executables
#
macro(exe1 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -c ${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ${src}1.c ../${FLEX_MyScanner_OUTPUTS} ../error.c
		../initmem.c ../initsym.c ../interp1.c ../joy.c
		../node.c ../optable.c ../print.c ../scan.c
		../symbol.c ../utils1.c)
target_link_libraries(${src}1 gc-lib)
endmacro(exe1)

macro(exe2 src)
add_custom_command(OUTPUT ${src}2.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -o ${src}.joy | clang-format >${src}2.c)
add_executable(${src}2 ${src}2.c ../${FLEX_MyScanner_OUTPUTS} ../error.c
		../initmem.c ../initsym.c ../interp1.c ../joy.c
		../node.c ../optable.c ../print.c ../scan.c
		../symbol.c ../utils1.c)
target_link_libraries(${src}2 gc-lib)
endmacro(exe2)

exe1(flatjoy)
exe1(gcd)
exe1(grmtst)
exe1(jp-church)
exe1(jp-joytst)
exe1(jp-nestrec)
exe1(jp-reprodtst)
exe1(laztst)
exe1(modtst)
exe1(mtrtst)
exe1(plgtst)
exe1(reptst)
exe1(symtst)
exe1(test)
exe1(joytut)
exe1(lsptst)
  
# exe2(flatjoy)
# exe2(gcd)
# # exe2(grmtst)
# exe2(jp-church)
# exe2(jp-joytst)
# exe2(jp-nestrec)
# exe2(jp-reprodtst)
# exe2(laztst)
# exe2(modtst)
# exe2(mtrtst)
# # exe2(plgtst)
# exe2(reptst)
# # exe2(symtst)
# exe2(test)
# exe2(joytut)
# # exe2(lsptst)
