/*
    module  : leql.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

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
