/*
    module  : unary.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef UNARY_X
#define UNARY_C

#ifdef NEW_RUNTIME

#ifndef STACK_C
#undef STACK_X
#include "stack.c"
#define STACK_X
#endif

#ifndef SWAP_C
#undef SWAP_X
#include "swap.c"
#define SWAP_X
#endif

#ifndef DIP_C
#undef DIP_X
#include "dip.c"
#define DIP_X
#endif

#ifndef REST_C
#undef REST_X
#include "rest.c"
#define REST_X
#endif

#ifndef CONS_C
#undef CONS_X
#include "cons.c"
#define CONS_X
#endif

#ifndef UNSTACK_C
#undef UNSTACK_X
#include "unstack.c"
#define UNSTACK_X
#endif

void do_unary(void)
{
    TRACE;
    do_stack();
    do_swap();
    do_dip();
    do_rest();
    do_rest();
    do_cons();
    do_unstack();
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
#endif
