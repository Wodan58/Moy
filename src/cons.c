/*
    module  : cons.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
#define PROCEDURE	do_cons
#define NAME		"cons"
#define AGGR		stk
#define ELEM		stk->next
#include "consswons.c"
