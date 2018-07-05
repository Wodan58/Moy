/*
    module  : %M%
    version : %I%
    date    : %G%
*/
#ifdef RUNTIME
void do_fadd(void)
{
    float dbl1, dbl2;

    TRACE;
    memcpy(&dbl1, &stk[-2], sizeof(float));
    memcpy(&dbl2, &stk[-1], sizeof(float));
    dbl1 += dbl2;
    memcpy(&stk[-2], &dbl1, sizeof(node_t));
    stk--;
}
#else
/**
.+  :  M I  ->  N
Numeric N is the result of adding integer I to numeric M.
Also supports float.
*/
#define PROCEDURE	do_fadd
#define NAME		"+"
#define OPER		+
#include "plusminus.h"
/* plus.c */
#endif
