/*
    module  : iffile.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
iffile  :  X [T] [E]  ->  ...
If X is a file, executes T else executes E.
*/
#define PROCEDURE	do_iffile
#define NAME		"iffile"
#define TYP		FILE_
#include "iftype.c"
