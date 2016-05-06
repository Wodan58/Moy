/*
    module  : ternary.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
ternary  :  X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
/* ternary.c */
#define PROCEDURE	ternary_
#define NAME		"ternary"
#define PARAMCOUNT	FOURPARAMS
#define TOP		stk->next->next->next
#include "n_ary.c"
