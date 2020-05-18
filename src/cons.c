/*
    module  : cons.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef CONS_C
#define CONS_C

/**
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_cons
#define NAME		"cons"
#define AGGR		stk
#define ELEM		stk->next
#include "consswons.h"
#endif
