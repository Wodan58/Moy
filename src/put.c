/*
    module  : put.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef PUT_C
#define PUT_C

/**
put  :  X  ->
Writes X to output, pops X off stack.
*/
PRIVATE void do_put(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("put");
    writefactor(env, env->stk, stdout);
    putchar(' ');
    POP(env->stk);
}
#endif
