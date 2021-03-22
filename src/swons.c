/*
    module  : swons.c
    version : 1.9
    date    : 03/15/21
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
#include "consswons.h"
#endif
