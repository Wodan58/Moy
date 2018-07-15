/*
    module  : plus.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef PLUS_X
#define PLUS_C

#ifdef NEW_RUNTIME
void do_plus(void)
{
    TRACE;
    stk[-2] += stk[-1];
    (void)do_pop();
}
#else
/**
+  :  M I  ->  N
Numeric N is the result of adding integer I to numeric M.
Also supports float.
*/
#define PROCEDURE	do_plus
#define NAME		"+"
#define OPER		+
#include "plusminus.h"
/* plus.c */
#endif
#endif
