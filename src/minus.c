/*
    module  : minus.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_minus(void)
{
    TRACE;
    stk[-2] -= stk[-1];
    stk--;
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
