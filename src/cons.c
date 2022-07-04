/*
    module  : cons.c
    version : 1.10
    date    : 06/20/22
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
#include "cons_swons.h"
/* cons.c */
#endif
