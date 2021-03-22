/*
    module  : greater.c
    version : 1.8
    date    : 03/15/21
*/
#ifndef GREATER_C
#define GREATER_C

/**
>  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than Y.  Also supports float.
*/
#define PROCEDURE	do_greater
#define NAME		">"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>
#define SETCMP		i!=j&&!(j&~i)
#include "comprel.h"
#endif
