/*
    module  : swons_set.c
    version : 1.2
    date    : 07/07/18
*/
#ifdef RUNTIME
void do_swons_set(void)
{
    TRACE;
    stk[-2] |= 1 << stk[-1];
    stk--;
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
