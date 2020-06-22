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

add_custom_target(test00.txt ALL
		  DEPENDS joy fib1 gcd1 test1 jp-joytst1 flatjoy1 jp-reprodtst1
			  modtst1 jp-nestrec1 laztst1 tutinp1 jp-church1
			  grmtst1 mtrtst1 reptst1 tutorial1 symtst1 plgtst1
			  lsptst1
		  COMMAND make -f regres.mak
		  COMMAND make -f regres1.mak
		  COMMAND touch test00.txt)
