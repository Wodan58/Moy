/*
    module  : of.c
    version : 1.10
    date    : 06/20/22
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
#include "of_at.h"
/* of.c */
#endif
