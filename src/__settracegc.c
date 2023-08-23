/*
    module  : __settracegc.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef __SETTRACEGC_C
#define __SETTRACEGC_C

/**
OK 2990  __settracegc  :  D	I  ->
Sets value of flag for tracing garbage collection to I (= 0..6).
*/
void __settracegc_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    env->tracegc = node.u.num;
}
#endif
