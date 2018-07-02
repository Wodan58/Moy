/*
    module  : greater.c
    version : 1.4
    date    : 07/02/18
*/

/**
>  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than Y.  Also supports float.
*/
#define PROCEDURE	do_greater
#define NAME		">"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>
#define SETCMP		i!=j&&!(j&~i)
#include "comprel.h"
