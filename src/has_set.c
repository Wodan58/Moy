/*
    module  : has_set.c
    version : 1.4
    date    : 07/15/18
*/
#ifndef HAS_SET_X
#define HAS_SET_C

#ifdef NEW_RUNTIME
void do_has_set(void)
{
    TRACE;
    stk[-2] = (stk[-2] & 1 << stk[-1]) != 0;
    do_pop();
}
#else
/**
has_set  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
#define PROCEDURE	do_has_set
#define CORRECT_INHAS_COMPARE
#define NAME		"has"
#define AGGR		stk->next
#define ELEM		stk
#include "inhas.h"
#endif
#endif
