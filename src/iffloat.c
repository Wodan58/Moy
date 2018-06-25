/*
    module  : iffloat.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
iffloat  :  X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
#define PROCEDURE	do_iffloat
#define NAME		"iffloat"
#define TYP		FLOAT_
#include "iftype.h"
/* iffloat.c */
