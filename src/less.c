/*
    module  : less.c
    version : 1.8
    date    : 03/15/21
*/
#ifndef LESS_C
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
