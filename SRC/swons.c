/*
    module  : swons.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
swons  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_swons
#define NAME		"swons"
#define AGGR		stk->next
#define ELEM		stk
#include "consswons.c"
