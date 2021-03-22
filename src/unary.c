/*
    module  : unary.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef UNARY_C
#define UNARY_C

/**
unary  :  X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
#define PROCEDURE	do_unary
#define NAME		"unary"
#define PARAMCOUNT	TWOPARAMS
#define TOP		env->stk->next
#define TOPSTR		"env->stk->next"
#define ARITY		1
#include "nary.h"
#endif
