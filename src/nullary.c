/*
    module  : nullary.c
    version : 1.10
    date    : 03/15/21
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
#define TOP		env->stk
#define TOPSTR		"env->stk"
#define ARITY		0
#include "nary.h"
#endif
