/*
    module  : neql.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef NEQL_X
#define NEQL_C

/**
!=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
#define PROCEDURE	do_neql
#define NAME		"!="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		!=
#define SETCMP		i!=j
#include "comprel.h"
#endif
