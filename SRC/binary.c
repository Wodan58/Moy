/*
    module  : binary.c
    version : 1.3
    date    : 10/23/17
*/
#include "runtime.h"

/*
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
#include "nary.c"
