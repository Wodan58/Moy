/*
    module  : iflist.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
iflist  :  X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
/* iflist.c */
#define PROCEDURE	iflist_
#define NAME		"iflist"
#define TYP		LIST_
#include "if_type.c"
