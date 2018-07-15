/*
    module  : swons.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef SWONS_X
#define SWONS_C

#ifdef NEW_RUNTIME
void do_swons(void)
{
    code_t *cur;

    TRACE;
    cur = joy_code();
    cur->num = do_pop();
    cur->next = (code_t *)stk[-1];
    stk[-1] = (node_t)cur;
}
#else
/**
swons  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_swons
#define NAME		"swons"
#define AGGR		stk->next
#define ELEM		stk
#include "consswons.h"
#endif
#endif
