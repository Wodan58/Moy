/*
    module  : enconcat.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
enconcat  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
PRIVATE void do_enconcat(void)
{
#ifndef NCHECK
    if (optimizing && stk->op == stk->next->op &&
	AGGREGATE(stk) && AGGREGATE(stk->next) && VALID(stk->next->next))
	;
    else
	COMPILE;
    THREEPARAMS("enconcat");
    SAME2TYPES("enconcat");
#endif
    do_swapd();
    do_cons();
    do_concat();
}
