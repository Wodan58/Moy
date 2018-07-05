/*
    module  : swons_str.c
    version : 1.1
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_swons_str(void)
{
    node_t ch;
    code_t *cur;
    char *ptr, *str;

    TRACE;
    ch = do_pop();
    ptr = (char *)stk[-1];
    if (ptr)
	str = malloc_sec(strlen(ptr) + 2);
    else
	str = malloc_sec(2);
    *str = ch;
    if (ptr)
	strcpy(str + 1, ptr);
    else
	str[1] = 0;
    stk[-1] = (node_t)str;
}
#else
/**
swons_str  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_swons_str
#define NAME		"swons_str"
#define AGGR		stk->next
#define ELEM		stk
#include "consswons.h"
#endif
