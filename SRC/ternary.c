/*
    module  : ternary.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
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
#include "nary.c"
