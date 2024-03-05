/*
    module  : pop.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef POP_C
#define POP_C

/**
Q0  OK  1320  pop  :  D  X  ->
Removes X from top of the stack.
*/
void pop_(pEnv env)
{
    PARM(1, ANYTYPE);
    env->stck = pvec_del(env->stck);
}
#endif
