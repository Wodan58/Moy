/*
    module  : nullary.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef NULLARY_C
#define NULLARY_C

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
#endif
