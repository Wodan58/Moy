/*
    module  : at.c
    version : 1.10
    date    : 06/20/22
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
#include "of_at.h"
/* at.c */
#endif
