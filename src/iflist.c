/*
    module  : iflist.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
iflist  :  X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
#define PROCEDURE	do_iflist
#define NAME		"iflist"
#define TYP		LIST_
#include "iftype.c"
