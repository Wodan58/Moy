/*
    module  : pop.c
    version : 1.5
    date    : 09/15/23
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
    (void)lst_pop(env->stck);
}
#endif
