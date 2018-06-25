/*
    module  : ifstring.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
ifstring  :  X [T] [E]  ->  ...
If X is a string, executes T else executes E.
*/
#define PROCEDURE	do_ifstring
#define NAME		"ifstring"
#define TYP		STRING_
#include "iftype.h"
/* ifstring.c */
