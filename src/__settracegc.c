/*
    module  : __settracegc.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef __SETTRACEGC_C
#define __SETTRACEGC_C

/**
__settracegc  :  I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
PRIVATE void do___settracegc(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("settracegc");
    NUMERICTYPE("settracegc");
    POP(stk);
}
#endif
