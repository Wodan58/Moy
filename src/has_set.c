/*
    module  : has_set.c
    version : 1.1
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_has_set(void)
{
    DEBUG;
    stk[-2] = (stk[-2] & 1 << stk[-1]) != 0;
    stk--;
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