/*
    module  : geql.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef GEQL_C
#define GEQL_C

/**
>=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is greater than or equal to Y.  Also supports float.
*/
#define PROCEDURE	do_geql
#define NAME		">="
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define OPR		>=
#define SETCMP		!(j&~i)
#include "comprel.h"
/* geql.c */
#endif
