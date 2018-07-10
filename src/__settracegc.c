/*
    module  : __settracegc.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef __SETTRACEGC_X
#define __SETTRACEGC_C

#ifdef RUNTIME
void do___settracegc(void)
{
    tracegc = do_pop();
}
#else
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
    POP(stk);
}
#endif
#endif
