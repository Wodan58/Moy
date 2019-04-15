/*
    module  : le.c
    version : 1.1
    date    : 04/15/19
*/
#ifndef LE_X
#define LE_C

/**
le  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than or equal to Y.  Also supports float.
*/
#define PROCEDURE	do_le
#define NAME		"<="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		<=
#define SETCMP		!(i&~j)
#include "comprel_str.h"
#endif
