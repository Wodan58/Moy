/*
    module  : of.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef OF_C
#define OF_C

/**
of  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
#define PROCEDURE	do_of
#define NAME		"of"
#define AGGR		env->stk
#define	INDEX		env->stk->next
#include "ofat.h"
#endif
