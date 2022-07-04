/*
    module  : put.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef PUT_C
#define PUT_C

/**
put  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put(pEnv env)
{
    COMPILE;
    ONEPARAM("put");
    writefactor(env, env->stk);
    putchar(' ');
    POP(env->stk);
}
#endif
