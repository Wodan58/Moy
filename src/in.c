/*
    module  : in.c
    version : 1.7
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_in(void)
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
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in
#define CORRECT_INHAS_COMPARE
#define NAME		"in"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.h"
#endif
