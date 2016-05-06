/*
    module  : iffile.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
iffile  :  X [T] [E]  ->  ...
If X is a file, executes T else executes E.
*/
/* iffile.c */
#define PROCEDURE	iffile_
#define NAME		"iffile"
#define TYP		FILE_
#include "if_type.c"
