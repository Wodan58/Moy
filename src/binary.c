/*
    module  : binary.c
    version : 1.9
    date    : 03/15/21
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
#define PARAMCOUNT	THREEPARAMS
#define TOP		env->stk->next->next
#define TOPSTR		"env->stk->next->next"
#define ARITY		2
#include "nary.h"
#endif
