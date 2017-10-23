/*
    module  : ifchar.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
ifchar  :  X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
#define PROCEDURE	do_ifchar
#define NAME		"ifchar"
#define TYP		CHAR_
#include "iftype.c"
