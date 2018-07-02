/*
    module  : ternary.c
    version : 1.5
    date    : 07/02/18
*/

/**
ternary  :  X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
#define PROCEDURE	do_ternary
#define NAME		"ternary"
#define PARAMCOUNT	FOURPARAMS
#define TOP		stk->next->next->next
#define TOPSTR		"stk->next->next->next"
#define ARITY		3
#include "nary.h"
