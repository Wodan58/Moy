/*
    module  : binary.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef BINARY_C
#define BINARY_C

/**
binary  :  X Y [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly two are removed from the stack.
*/
#define PROCEDURE	do_binary
#define NAME		"binary"
#define TOP		env->stk->next->next
#define TOPSTR		"env->stk->next->next"
#include "n_ary.h"
/* binary.c */
#endif
