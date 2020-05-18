#
#	Makefile for MOY executables
#

macro(exe1 src)
add_custom_command(OUTPUT ${src}1.c
		   DEPENDS joy ${src}.joy
		   COMMAND joy -c ${src}.joy | clang-format >${src}1.c)
add_executable(${src}1 ../main.c ${src}1.c ../initsym.c ../node.c ../memory.c
               ../utils.c ../yylex.c ../print.c ../runtime.c)
target_link_libraries(${src}1 gc-lib)
endmacro(exe1)

exe1(fib)
exe1(gcd)
exe1(test)
exe1(jp-joytst)
exe1(flatjoy)
exe1(jp-reprodtst)
exe1(modtst)
exe1(jp-nestrec)
exe1(laztst)
exe1(tutinp)
exe1(jp-church)
exe1(grmtst)
exe1(mtrtst)
exe1(reptst)
exe1(tutorial)
exe1(symtst)
exe1(plgtst)
exe1(lsptst)
