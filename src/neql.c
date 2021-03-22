/*
    module  : neql.c
    version : 1.8
    date    : 03/15/21
*/
#ifndef NEQL_C
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
