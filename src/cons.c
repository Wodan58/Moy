/*
    module  : cons.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef CONS_C
#define CONS_C

/**
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_cons
#define NAME		"cons"
#define AGGR		env->stk
#define ELEM		env->stk->next
#include "consswons.h"
#endif
