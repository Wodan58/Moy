/*
    module  : ifset.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
ifset  :  X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
/* ifset.c */
#define PROCEDURE	ifset_
#define NAME		"ifset"
#define TYP		SET_
#include "if_type.c"
