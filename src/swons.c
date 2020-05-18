/*
    module  : swons.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef SWONS_C
#define SWONS_C

/**
swons  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_swons
#define NAME		"swons"
#define AGGR		stk->next
#define ELEM		stk
#include "consswons.h"
#endif
