/*
    module  : eql.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X equal to Y.  Also supports float.
*/
/* eql.c */
#define PROCEDURE	eql_
#define NAME		"="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		==
#define SETCMP		i==j
#include "comprel.c"
