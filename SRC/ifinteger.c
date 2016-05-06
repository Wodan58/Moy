/*
    module  : ifinteger.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
ifinteger  :  X [T] [E]  ->  ...
If X is an integer, executes T else executes E.
*/
/* ifinteger.c */
#define PROCEDURE	ifinteger_
#define NAME		"ifinteger"
#define TYP		INTEGER_
#include "if_type.c"
