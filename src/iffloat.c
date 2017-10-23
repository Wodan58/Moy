/*
    module  : iffloat.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
iffloat  :  X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
#define PROCEDURE	do_iffloat
#define NAME		"iffloat"
#define TYP		FLOAT_
#include "iftype.c"
