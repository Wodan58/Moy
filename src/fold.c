/*
    module  : fold.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
fold  :  A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
PRIVATE void do_fold(void)
{
#ifndef NCHECK
    if (optimizing && LIST_1 && VALID(stk->next) && VALID(stk->next->next))
	;
    else
	COMPILE;
    THREEPARAMS("fold");
#endif
    do_swapd();
    do_step();
}
