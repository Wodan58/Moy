#
#   module  : CMakeLists.txt
#   version : 1.7
#   date    : 02/13/24
#
macro(exe9 src)
add_custom_target(${src}.out ALL
		  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test/${src}.joy
		  COMMAND joy ${CMAKE_SOURCE_DIR}/test/${src}.joy >${src}.out)
endmacro(exe9)

exe9(m20)
exe9(m21)
exe9(test01)
exe9(test02)
exe9(test03)
exe9(test06)
exe9(test07)
exe9(test08)
exe9(test09)
exe9(test10)
exe9(test11)
exe9(test12)
exe9(test13)
exe9(test14)
exe9(test15)
exe9(test16)
exe9(test17)
# exe9(test18)	too many heap sections
exe9(test19)
exe9(test20)
exe9(test21)
exe9(test22)
exe9(test23)
exe9(test25)
exe9(test29)
exe9(test30)
exe9(test31)
exe9(test32)
exe9(test33)

#
#  Taking parameter 10 and redirecting
#
add_custom_target(test04.out ALL
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test/test04.joy
		  COMMAND joy 10 <${CMAKE_SOURCE_DIR}/test/test04.joy
                          >test04.out)

#
#  Taking parameter test05.joy
#
add_custom_target(test05.out ALL
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test/test05.joy
		  COMMAND joy ${CMAKE_SOURCE_DIR}/test/test05.joy
                          ${CMAKE_SOURCE_DIR}/test/test05.joy >test05.out)

#
#  Test not open file
#
add_custom_target(test24.out ALL
                  DEPENDS joy
                  COMMAND joy nonexist)

#
#  Test rest of options
#
add_custom_target(test26.out ALL
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test/test26.joy
		  COMMAND joy -vs <${CMAKE_SOURCE_DIR}/test/test26.joy >test26.out)

add_custom_target(test27.out ALL
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test/test27.joy
		  COMMAND joy -wh ${CMAKE_SOURCE_DIR}/test/test27.joy >test27.out)

add_custom_target(test28.out ALL
		  DEPENDS joy ${CMAKE_SOURCE_DIR}/test/test28.joy
		  COMMAND joy -d <${CMAKE_SOURCE_DIR}/test/test28.joy >test28.out)
