/*
    module  : iffloat.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
iffloat  :  X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
/* iffloat.c */
#define PROCEDURE	iffloat_
#define NAME		"iffloat"
#define TYP		FLOAT_
#include "if_type.c"
