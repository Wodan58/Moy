/*
    module  : pop.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef POP_C
#define POP_C

/**
pop  :  X  ->
Removes X from top of the stack.
*/
PRIVATE void do_pop(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("pop");
    POP(env->stk);
}
#endif
