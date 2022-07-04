/*
    module  : nullary.c
    version : 1.11
    date    : 06/20/22
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
#define TOP		env->stk
#define TOPSTR		"env->stk"
#include "n_ary.h"
/* nullary.c */
#endif
