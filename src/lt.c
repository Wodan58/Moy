/*
    module  : lt.c
    version : 1.1
    date    : 04/15/19
*/
#ifndef LT_X
#define LT_C

/**
lt  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than Y.  Also supports float.
*/
#define PROCEDURE	do_lt
#define NAME		"<"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		<
#define SETCMP		i!=j&&!(i&~j)
#include "comprel_str.h"
#endif
