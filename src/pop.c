/*
    module  : pop.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef POP_C
#define POP_C

/**
pop  :  X  ->
Removes X from top of the stack.
*/
PRIVATE void do_pop(pEnv env)
{
    ONEPARAM("pop");
    POP(env->stk);
}
#endif
