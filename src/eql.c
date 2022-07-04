/*
    module  : eql.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef EQL_C
#define EQL_C

/**
=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is equal to Y.  Also supports float.
*/
#define PROCEDURE	do_eql
#define NAME		"="
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define OPR		==
#define SETCMP		i==j
#include "comprel.h"
/* eql.c */
#endif
