/*
    module  : ifchar.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
ifchar  :  X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
/* ifchar.c */
#define PROCEDURE	ifchar_
#define NAME		"ifchar"
#define TYP		CHAR_
#include "if_type.c"
