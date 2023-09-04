/*
    module  : pop.c
    version : 1.3
    date    : 09/04/23
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
