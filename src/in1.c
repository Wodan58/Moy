/*
    module  : in1.c
    version : 1.5
    date    : 05/12/19
*/
#ifndef IN1_X
#define IN1_C

#ifdef NEW_RUNTIME
void do_in1(void)
{
    code_t *cur;

    TRACE;
    for (cur = (code_t *)do_pop(); cur; cur = cur->next)
	if (stk[-1] == cur->num)
	    break;
    stk[-1] = cur != 0;
}
#else
/**
in1  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in1
#ifdef CORRECT_INHAS_COMPARE
#undef CORRECT_INHAS_COMPARE
#endif
#define NAME		"in1"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.h"
#endif
#endif
