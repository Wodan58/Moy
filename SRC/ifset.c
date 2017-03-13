/*
    module  : ifset.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
ifset  :  X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
#define PROCEDURE	do_ifset
#define NAME		"ifset"
#define TYP		SET_
#include "iftype.c"
