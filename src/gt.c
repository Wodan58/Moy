/*
    module  : gt.c
    version : 1.1
    date    : 04/15/19
*/
#ifndef GT_X
#define GT_C

/**
gt  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than Y.  Also supports float.
*/
#define PROCEDURE	do_gt
#define NAME		">"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>
#define SETCMP		i!=j&&!(j&~i)
#include "comprel_str.h"
#endif
