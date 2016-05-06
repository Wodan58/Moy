/*
    module  : ifstring.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
ifstring  :  X [T] [E]  ->  ...
If X is a string, executes T else executes E.
*/
/* ifstring.c */
#define PROCEDURE	ifstring_
#define NAME		"ifstring"
#define TYP		STRING_
#include "if_type.c"
