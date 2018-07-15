/*
    module  : has.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef HAS_X
#define HAS_C

#ifdef NEW_RUNTIME
void do_has(void)
{
    node_t num;
    code_t *cur;

    TRACE;
    for (num = do_pop(), cur = (code_t *)stk[-1]; cur; cur = cur->next)
	if (num == cur->num)
	    break;
    stk[-1] = cur != 0;
}
#else
/**
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
#define PROCEDURE	do_has
#define CORRECT_INHAS_COMPARE
#define NAME		"has"
#define AGGR		stk->next
#define ELEM		stk
#include "inhas.h"
#endif
#endif
