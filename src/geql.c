/*
    module  : geql.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef GEQL_X
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
