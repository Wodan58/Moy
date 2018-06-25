/*
    module  : iflist.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
iflist  :  X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
#define PROCEDURE	do_iflist
#define NAME		"iflist"
#define TYP		LIST_
#include "iftype.h"
/* iflist.c */
