/*
    module  : binary.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef BINARY_X
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
#define TOP		stk->next->next
#define TOPSTR		"stk->next->next"
#define ARITY		2
#include "nary.h"
#endif
