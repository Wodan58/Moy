#
#	Makefile for MOY executables
#
macro(exe src)
add_custom_target(${src}.c DEPENDS moy ${src}.joy)
add_custom_command(OUTPUT ${src}.c
		   COMMAND moy -o ${src}.joy | clang-format >${src}.c
		   COMMAND rm -f ${src}.sym)
add_executable(${src} ${src}.c)
target_link_libraries(${src} joy /usr/local/lib/libgc-lib.a)
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
