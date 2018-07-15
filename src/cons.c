/*
    module  : cons.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef CONS_X
#define CONS_C

#ifdef NEW_RUNTIME
void do_cons(void)
{
    code_t *cur;

    TRACE;
    cur = joy_code();
    cur->next = (code_t *)do_pop();
    cur->num = stk[-1];
    stk[-1] = (node_t)cur;
}
#else
/**
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_cons
#define NAME		"cons"
#define AGGR		stk
#define ELEM		stk->next
#include "consswons.h"
#endif
#endif
