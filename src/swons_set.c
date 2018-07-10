/*
    module  : swons_set.c
    version : 1.3
    date    : 07/10/18
*/
#ifndef SWONS_SET_X
#define SWONS_SET_C

#ifdef RUNTIME
void do_swons_set(void)
{
    TRACE;
    stk[-2] |= 1 << stk[-1];
    (void)do_pop();
}
#else
/**
swons_set  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_swons_set
#define NAME		"swons"
#define AGGR		stk->next
#define ELEM		stk
#include "consswons.h"
#endif
#endif
