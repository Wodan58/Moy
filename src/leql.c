/*
    module  : leql.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef LEQL_X
#define LEQL_C

/**
<=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than or equal to Y.  Also supports float.
*/
#define PROCEDURE	do_leql
#define NAME		"<="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		<=
#define SETCMP		!(i&~j)
#include "comprel.h"
#endif
