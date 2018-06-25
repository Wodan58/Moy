/*
    module  : ifinteger.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
ifinteger  :  X [T] [E]  ->  ...
If X is an integer, executes T else executes E.
*/
#define PROCEDURE	do_ifinteger
#define NAME		"ifinteger"
#define TYP		INTEGER_
#include "iftype.h"
/* ifinteger.c */
