/*
    module  : unary.c
    version : 1.6
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_unary(void)
{
    void do_unstack(void);

    TRACE;
    do_stack();
    do_swap();
    do_dip();
    do_rest();
    do_rest();
    do_cons();
    do_unstack();
//  execute((code_t *)do_pop());
}
#else
/**
unary  :  X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
#define PROCEDURE	do_unary
#define NAME		"unary"
#define PARAMCOUNT	TWOPARAMS
#define TOP		stk->next
#define TOPSTR		"stk->next"
#define ARITY		1
#include "nary.h"
#endif
