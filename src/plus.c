/*
    module  : plus.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_plus(void)
{
    TRACE;
    stk[-2] += stk[-1];
    stk--;
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
