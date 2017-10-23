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

exe(flatjoy)
exe(gcd)
exe(grmtst)
exe(joytut)
exe(jp-church)
exe(jp-joytst)
exe(jp-nestrec)
exe(jp-reprodtst)
exe(laztst)
exe(lsptst)
exe(modtst)
exe(mtrtst)
exe(plgtst)
exe(reptst)
exe(symtst)
exe(test1)
