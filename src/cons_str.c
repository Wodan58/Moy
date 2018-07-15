/*
    module  : cons_str.c
    version : 1.3
    date    : 07/15/18
*/
#ifndef CONS_STR_X
#define CONS_STR_C

#ifdef NEW_RUNTIME
void do_cons_str(void)
{
    size_t i;
    char *str, *result;

    TRACE;
    str = (char *)do_pop();
    i = str ? strlen(str) : 0;
    result = malloc_sec(i + 2);
    result[0] = stk[-1];
    if (str)
	strcpy(result + 1, str);
    else
	result[1] = 0;
    stk[-1] = (node_t)result;
}
#else
/**
cons_str  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_cons_str
#define NAME		"cons_str"
#define AGGR		stk
#define ELEM		stk->next
#include "consswons.h"
#endif
#endif
