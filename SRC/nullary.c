/*
    module  : nullary.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
nullary  :  [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
/* nullary.c */
#define PROCEDURE	nullary_
#define NAME		"nullary"
#define PARAMCOUNT	ONEPARAM
#define TOP		stk
#include "n_ary.c"
