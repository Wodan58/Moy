/*
    module  : less.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef LESS_C
#define LESS_C

/**
<  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is less than Y.  Also supports float.
*/
#define PROCEDURE	do_less
#define NAME		"<"
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define OPR		<
#define SETCMP		i!=j&&!(i&~j)
#include "comprel.h"
/* less.c */
#endif
