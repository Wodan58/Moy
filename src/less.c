/*
    module  : less.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef LESS_X
#define LESS_C

/**
<  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than Y.  Also supports float.
*/
#define PROCEDURE	do_less
#define NAME		"<"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		<
#define SETCMP		i!=j&&!(i&~j)
#include "comprel.h"
#endif
