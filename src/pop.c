/*
    module  : pop.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef POP_C
#define POP_C

/**
OK 1320  pop  :  D 	X  ->
Removes X from top of the stack.
*/
void pop_(pEnv env)
{
#ifndef COMPILER
    PARM(1, ANYTYPE);
    (void)lst_pop(env->stck);
#endif
}
#endif
