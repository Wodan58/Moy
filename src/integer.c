/*
    module  : integer.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
integer  :  X  ->  B
Tests whether X is an integer.
*/
#define PROCEDURE	do_integer
#define NAME		"integer"
#define REL		==
#define TYP		INTEGER_
#include "type.c"
