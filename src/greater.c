/*
    module  : greater.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef GREATER_C
#define GREATER_C

/**
>  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is greater than Y.  Also supports float.
*/
#define PROCEDURE	do_greater
#define NAME		">"
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define OPR		>
#define SETCMP		i!=j&&!(j&~i)
#include "comprel.h"
/* greater.c */
#endif
