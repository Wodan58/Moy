/*
    module  : pop.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef POP_C
#define POP_C

/**
OK 1320  pop  :  D 	X  ->
Removes X from top of the stack.
*/
void pop_(pEnv env)
{
    PARM(1, ANYTYPE);
    env->stck = pvec_del(env->stck);
}
#endif
