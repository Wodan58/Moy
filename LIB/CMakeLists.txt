#
#  Makefile for MOY
#
macro(exe src)
add_custom_target(${src}.c DEPENDS ${src}.joy)
add_custom_command(OUTPUT ${src}.c
		   COMMAND moy -c ${src}.joy >${src}.c
		   DEPENDS moy ${src}.joy)
add_executable(${src} ../main2.c ${src}.c)
target_link_libraries(${src} joy /usr/local/lib/libgc-lib.a)
endmacro(exe)

exe(tut)
exe(test1)
exe(tutinp2)
exe(jp-reprodtst)
exe(flatjoy)
exe(jp-church)
exe(reptst)
exe(symtst)
exe(jp-joytst)
exe(plgtst)
exe(lsptst2)
exe(laztst)
exe(jp-nestrec)
exe(grmtst)
