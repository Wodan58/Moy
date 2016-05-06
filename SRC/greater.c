/*
    module  : greater.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
>  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than Y.  Also supports float.
*/
/* greater.c */
#define PROCEDURE	greater_
#define NAME		">"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>
#define SETCMP		i!=j&&!(j&~i)
#include "comprel.c"
