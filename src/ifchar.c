/*
    module  : ifchar.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
ifchar  :  X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
#define PROCEDURE	do_ifchar
#define NAME		"ifchar"
#define TYP		CHAR_
#include "iftype.h"
/* ifchar.c */
