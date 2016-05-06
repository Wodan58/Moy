/*
    module  : binary.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
binary  :  X Y [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly two are removed from the stack.
*/
/* binary.c */
#define PROCEDURE	binary_
#define NAME		"binary"
#define PARAMCOUNT	THREEPARAMS
#define TOP		stk->next->next
#include "n_ary.c"
