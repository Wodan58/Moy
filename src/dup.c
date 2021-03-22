/*
    module  : dup.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef DUP_C
#define DUP_C

/**
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
PRIVATE void do_dup(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("dup");
    DUPLICATE(env->stk);
}
#endif
