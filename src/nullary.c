/*
    module  : nullary.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
nullary  :  [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
#define PROCEDURE	do_nullary
#define NAME		"nullary"
#define PARAMCOUNT	ONEPARAM
#define TOP		stk
#define TOPSTR		"stk"
#define ARITY		0
#include "nary.h"
