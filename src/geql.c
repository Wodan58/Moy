/*
    module  : geql.c
    version : 1.8
    date    : 03/15/21
*/
#ifndef GEQL_C
#define GEQL_C

/**
>=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than or equal to Y.  Also supports float.
*/
#define PROCEDURE	do_geql
#define NAME		">="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>=
#define SETCMP		!(j&~i)
#include "comprel.h"
#endif
