/*
    module  : eq.c
    version : 1.1
    date    : 04/15/19
*/
#ifndef EQ_X
#define EQ_C

/**
eq  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X equal to Y.  Also supports float.
*/
#define PROCEDURE	do_eq
#define NAME		"="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		==
#define SETCMP		i==j
#include "comprel_str.h"
#endif
