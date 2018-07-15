/*
    module  : of.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef OF_X
#define OF_C

#ifdef NEW_RUNTIME
void do_of(void)
{
    int i;
    code_t *cur;

    TRACE;
    for (cur = (code_t *)do_pop(), i = stk[-1]; i > 0; i--)
	cur = cur->next;
    stk[-1] = cur->num;
}
#else
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
#endif
