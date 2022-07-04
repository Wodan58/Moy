/*
    module  : swons.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef SWONS_C
#define SWONS_C

/**
swons  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_swons
#define NAME		"swons"
#define AGGR		env->stk->next
#define ELEM		env->stk
#include "cons_swons.h"
/* swons.c */
#endif
