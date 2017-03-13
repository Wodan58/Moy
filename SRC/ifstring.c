/*
    module  : ifstring.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
ifstring  :  X [T] [E]  ->  ...
If X is a string, executes T else executes E.
*/
#define PROCEDURE	do_ifstring
#define NAME		"ifstring"
#define TYP		STRING_
#include "iftype.c"
