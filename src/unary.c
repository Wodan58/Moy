/*
    module  : unary.c
    version : 1.11
    date    : 06/20/22
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
#define TOP		env->stk->next
#define TOPSTR		"env->stk->next"
#include "n_ary.h"
/* unary.c */
#endif
