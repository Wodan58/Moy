/*
    module  : leql.c
    version : 1.4
    date    : 07/02/18
*/

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
