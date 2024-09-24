#
#   module  : CmakeLists.txt
#   version : 1.2
#   date    : 09/19/24
#
macro(exe9 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy -w ${CMAKE_SOURCE_DIR}/test1/${src}.joy >${src}.out)
endmacro(exe9)

# test most options
macro(exe8 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy -a2de3g1lpru1 ${CMAKE_SOURCE_DIR}/test1/${src}.joy >${src}.out)
endmacro(exe8)

# test rest of options
macro(exe7 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy -hivx ${CMAKE_SOURCE_DIR}/test1/${src}.joy >${src}.out)
endmacro(exe7)

# test unknown options
macro(exe6 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy -z ${CMAKE_SOURCE_DIR}/test1/${src}.joy dummy >${src}.out)
endmacro(exe6)

# test tracing and symbol table
macro(exe5 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy -st ${CMAKE_SOURCE_DIR}/test1/${src}.joy dummy >${src}.out)
endmacro(exe5)

#test access to nonexisting file
macro(exe4 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy dummy ${CMAKE_SOURCE_DIR}/test1/${src}.joy >${src}.out)
endmacro(exe4)

#test input from stdin
macro(exe3 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy <${CMAKE_SOURCE_DIR}/test1/${src}.joy >${src}.out)
endmacro(exe3)

#test dump of tokens
macro(exe2 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test1
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test1/${src}.joy
		  COMMAND joy -p ${CMAKE_SOURCE_DIR}/test1/${src}.joy >${src}.out)
endmacro(exe2)

exe3(main5)
exe4(exist)
exe5(tut)
exe6(minim)
exe7(empty)
exe8(scan)
exe9(parm)
exe2(const)
exe9(quad)
exe9(incl)
exe9(m20)
exe9(m21)
exe9(m22)
exe9(m23)
exe9(m24)
exe2(m25)
exe9(m26)
exe9(errors)
exe2(scan1)
exe9(extra)
