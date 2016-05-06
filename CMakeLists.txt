#
#  Makefile for MOY
#
cmake_minimum_required(VERSION 3.0)
project(Moy VERSION 1.01)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
add_definitions(-D_CRT_SECURE_NO_WARNINGS -DBIT_32 -I.)
add_executable(moy ${BISON_MyParser_OUTPUTS} main1.c compile.c)
target_link_libraries(moy /usr/local/lib/joy.lib /usr/local/lib/gc-lib.lib -NOD:LIBCMT)
