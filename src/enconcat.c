/*
    module  : enconcat.c
    version : 1.5
    date    : 07/02/18
*/

/**
enconcat  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
PRIVATE void do_enconcat(void)
{
#ifndef NCHECK
    if (compiling && VALID_3 && AGGREGATE_1 && AGGREGATE_2 &&
	stk->op == stk->next->op)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("enconcat");
    SAME2TYPES("enconcat");
    do_swapd();
    do_cons();
    do_concat();
}
