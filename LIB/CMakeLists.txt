#
#  Makefile for MOY
#
macro(exe src)
add_custom_target(${src}.c DEPENDS ${src}.joy)
add_custom_command(OUTPUT ${src}.c
		   COMMAND moy -c ${src}.joy | clang-format >${src}.c
		   DEPENDS moy ${src}.joy)
add_executable(${src} ../main2.c ${src}.c)
target_link_libraries(${src} joy gc-lib)
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
#exe(alljoy)
