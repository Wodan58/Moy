/*
    module  : cons.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
/* cons.c */
#define PROCEDURE	cons_
#define NAME		"cons"
#define AGGR		stk
#define ELEM		stk->next
#include "cons_swons.c"
