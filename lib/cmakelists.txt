#
#	Makefile for MOY executables
#
macro(exe src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS moy ${src}.joy
		   COMMAND moy -o ${src}.joy >${src}.c)
add_executable(${src} ${src}.c)
target_link_libraries(${src} joy gc-lib)
endmacro(exe)

exe(fib)
exe(test1)
exe(gcd)
exe(modtst)
exe(jp-joytst)
exe(tutinp2)
exe(laztst)
exe(lsptst2)
exe(flatjoy)
exe(jp-reprodtst)
exe(reptst)
exe(tut)
exe(grmtst)
exe(plgtst)
exe(mtrtst)
exe(jp-nestrec)
exe(symtst)
exe(jp-church)
