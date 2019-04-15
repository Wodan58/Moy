/*
    module  : ge.c
    version : 1.1
    date    : 04/15/19
*/
#ifndef GE_X
#define GE_C

/**
ge  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than or equal to Y.  Also supports float.
*/
#define PROCEDURE	do_ge
#define NAME		">="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>=
#define SETCMP		!(j&~i)
#include "comprel_str.h"
#endif
