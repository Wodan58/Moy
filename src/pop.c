/*
    module  : pop.c
    version : 1.9
    date    : 11/20/24
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
    vec_reduce(env->stck, 1);
}
#endif
