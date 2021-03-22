/*
    module  : at.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef AT_C
#define AT_C

/**
at  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
#define PROCEDURE	do_at
#define NAME		"at"
#define AGGR		env->stk->next
#define	INDEX		env->stk
#include "ofat.h"
#endif
