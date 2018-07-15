/*
    module  : max.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef MAX_X
#define MAX_C

#ifdef NEW_RUNTIME
void do_max(void)
{
    TRACE;
    if (stk[-2] < stk[-1])
	stk[-2] = stk[-1];
    (void)do_pop();
}
#else
/**
max  :  N1 N2  ->  N
N is the maximum of numeric values N1 and N2.  Also supports float.
*/
#define PROCEDURE	do_max
#define NAME		"max"
#define OPER		<
#include "maxmin.h"
/* max.c */
#endif
#endif
