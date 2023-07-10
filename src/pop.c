/*
    module  : pop.c
    version : 1.1
    date    : 07/10/23
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
    (void)vec_pop(env->stck);
}
#endif
