/*
    module  : __settracegc.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
__settracegc  :  I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
PRIVATE void do___settracegc(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("settracegc");
    NUMERICTYPE("settracegc");
#endif
    tracegc = stk->u.num;
    POP(stk);
}
