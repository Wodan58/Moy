/*
    module  : of.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef OF_C
#define OF_C

/**
of  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
#define PROCEDURE	do_of
#define NAME		"of"
#define AGGR		stk
#define	INDEX		stk->next
#include "ofat.h"
#endif
