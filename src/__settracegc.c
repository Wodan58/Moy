/*
    module  : __settracegc.c
    version : 1.7
    date    : 07/05/18
*/
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
