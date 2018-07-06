/*
    module  : nullary.c
    version : 1.6
    date    : 07/06/18
*/
#ifdef RUNTIME
void do_nullary(void)
{
    void do_stack(void), do_swap(void), do_rest(void), do_unstack(void);

    TRACE;
    do_stack();
    do_swap();
    do_dip();
    do_rest();
    do_cons();
    do_unstack();
}
#else
/**
nullary  :  [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
#define PROCEDURE	do_nullary
#define NAME		"nullary"
#define PARAMCOUNT	ONEPARAM
#define TOP		stk
#define TOPSTR		"stk"
#define ARITY		0
#include "nary.h"
#endif
