/*
    module  : swons.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
swons  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
/* swons.c */
#define PROCEDURE	swons_
#define NAME		"swons"
#define AGGR		stk->next
#define ELEM		stk
#include "cons_swons.c"
