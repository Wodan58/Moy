/*
    module  : __settracegc.c
    version : 1.6
    date    : 07/02/18
*/

/**
__settracegc  :  I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
PRIVATE void do___settracegc(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("settracegc");
    NUMERICTYPE("settracegc");
    tracegc = stk->u.num;
    POP(stk);
}
