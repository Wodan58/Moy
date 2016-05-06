/*
    module  : unary.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
unary  :  X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
/* unary.c */
#define PROCEDURE	unary_
#define NAME		"unary"
#define PARAMCOUNT	TWOPARAMS
#define TOP		stk->next
#include "n_ary.c"
