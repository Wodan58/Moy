/*
    module  : unary.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

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