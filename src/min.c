/*
    module  : min.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef MIN_X
#define MIN_C

#ifdef NEW_RUNTIME
void do_min(void)
{
    TRACE;
    if (stk[-2] > stk[-1])
	stk[-2] = stk[-1];
    (void)do_pop();
}
#else
/**
min  :  N1 N2  ->  N
N is the minimum of numeric values N1 and N2.  Also supports float.
*/
#define PROCEDURE	do_min
#define NAME		"min"
#define OPER		>
#include "maxmin.h"
/* min.c */
#endif
#endif
