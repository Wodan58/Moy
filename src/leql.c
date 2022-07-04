/*
    module  : leql.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef LEQL_C
#define LEQL_C

/**
<=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is less than or equal to Y.  Also supports float.
*/
#define PROCEDURE	do_leql
#define NAME		"<="
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define OPR		<=
#define SETCMP		!(i&~j)
#include "comprel.h"
/* leql.c */
#endif
