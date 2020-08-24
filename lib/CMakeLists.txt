add_custom_target(test15.txt ALL
		  DEPENDS joy
		  COMMAND ../joy fib.joy >test15.txt)
add_custom_target(test16.txt ALL
		  DEPENDS joy
		  COMMAND ../joy gcd.joy 24 54 >test16.txt)
add_custom_target(test17.txt ALL
		  DEPENDS joy
		  COMMAND ../joy test.joy >test17.txt)
add_custom_target(test18.txt ALL
		  DEPENDS joy
		  COMMAND ../joy flatjoy.joy >test18.txt)
add_custom_target(test19.txt ALL
		  DEPENDS joy
		  COMMAND ../joy jp-reprodtst.joy >test19.txt)
add_custom_target(test20.txt ALL
		  DEPENDS joy
		  COMMAND ../joy jp-nestrec.joy >test20.txt)
add_custom_target(test21.txt ALL
		  DEPENDS joy
		  COMMAND ../joy laztst.joy >test21.txt)
add_custom_target(test22.txt ALL
		  DEPENDS joy
		  COMMAND ../joy jp-church.joy >test22.txt)
add_custom_target(test23.txt ALL
		  DEPENDS joy
		  COMMAND ../joy grmtst.joy >test23.txt)
add_custom_target(test24.txt ALL
		  DEPENDS joy
		  COMMAND ../joy mtrtst.joy >test24.txt)
add_custom_target(test25.txt ALL
		  DEPENDS joy
		  COMMAND ../joy reptst.joy >test25.txt)
add_custom_target(test26.txt ALL
		  DEPENDS joy
		  COMMAND ../joy tutorial.joy >test26.txt)
add_custom_target(test27.txt ALL
		  DEPENDS joy
		  COMMAND ../joy symtst.joy >test27.txt)
add_custom_target(test28.txt ALL
		  DEPENDS joy
		  COMMAND ../joy plgtst.joy >test28.txt)
add_custom_target(test29.txt ALL
		  DEPENDS joy
		  COMMAND ../joy jp-joytst.joy >test29.txt)
add_custom_target(test30.txt ALL
		  DEPENDS joy
		  COMMAND ../joy modtst.joy >test30.txt)
add_custom_target(test31.txt ALL
		  DEPENDS joy
		  COMMAND cat tutinp.joy tutinp.inp | ../joy -s >test31.txt)
add_custom_target(test32.txt ALL
		  DEPENDS joy
		  COMMAND cat lsptst.joy lsptst.inp | ../joy -s >test32.txt)

#
#	executables
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
		  COMMAND make -f regres1.mak
		  COMMAND touch test00.txt)
