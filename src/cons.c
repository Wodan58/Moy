/*
    module  : cons.c
    version : 1.4
    date    : 07/02/18
*/

/**
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_cons
#define NAME		"cons"
#define AGGR		stk
#define ELEM		stk->next
#include "consswons.h"
