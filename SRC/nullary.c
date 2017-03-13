/*
    module  : nullary.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
nullary  :  [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
#define PROCEDURE	do_nullary
#define NAME		"nullary"
#define PARAMCOUNT	ONEPARAM
#define TOP		stk
#define TOPSTR		"stk"
#include "nary.c"
