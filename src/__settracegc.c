/*
    module  : __settracegc.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef __SETTRACEGC_X
#define __SETTRACEGC_C

#ifdef NEW_RUNTIME
void do___settracegc(void)
{
    TRACE;
    tracegc = do_pop();
}
#else
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
#endif
