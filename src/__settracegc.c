/*
    module  : __settracegc.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef __SETTRACEGC_C
#define __SETTRACEGC_C

/**
__settracegc  :  I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
PRIVATE void do___settracegc(pEnv env)
{
    COMPILE;
    ONEPARAM("settracegc");
    NUMERICTYPE("settracegc");
    POP(env->stk);
}
#endif
