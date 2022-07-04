/*
    module  : neql.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef NEQL_C
#define NEQL_C

/**
!=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is not equal to Y.  Also supports float.
*/
#define PROCEDURE	do_neql
#define NAME		"!="
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define OPR		!=
#define SETCMP		i!=j
#include "comprel.h"
/* neql.c */
#endif
