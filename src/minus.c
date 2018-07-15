/*
    module  : minus.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef MINUS_X
#define MINUS_C

#ifdef NEW_RUNTIME
void do_minus(void)
{
    TRACE;
    stk[-2] -= stk[-1];
    (void)do_pop();
}
#else
/**
-  :  M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
Also supports float.
*/
#define PROCEDURE	do_minus
#define NAME		"-"
#define OPER		-
#include "plusminus.h"
/* minus.c */
#endif
#endif
