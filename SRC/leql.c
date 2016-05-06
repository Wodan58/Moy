/*
    module  : leql.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
<=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than or equal to Y.  Also supports float.
*/
/* leql.c */
#define PROCEDURE	leql_
#define NAME		"<="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		<=
#define SETCMP		!(i&~j)
#include "comprel.c"
