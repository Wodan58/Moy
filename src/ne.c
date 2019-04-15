/*
    module  : ne.c
    version : 1.1
    date    : 04/15/19
*/
#ifndef NE_X
#define NE_C

/**
ne  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
#define PROCEDURE	do_ne
#define NAME		"!="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		!=
#define SETCMP		i!=j
#include "comprel_str.h"
#endif
