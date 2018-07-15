/*
    module  : eql.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef EQL_X
#define EQL_C

/**
=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X equal to Y.  Also supports float.
*/
#define PROCEDURE	do_eql
#define NAME		"="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		==
#define SETCMP		i==j
#include "comprel.h"
#endif
