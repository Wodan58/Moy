/*
    module  : eql.c
    version : 1.8
    date    : 03/15/21
*/
#ifndef EQL_C
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
