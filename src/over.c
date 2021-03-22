/*
    module  : over.c
    version : 1.7
    date    : 03/15/21
*/
#ifndef OVER_C
#define OVER_C

/**
over  :  X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
PRIVATE void do_over(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("over");
    DUPLICATE(env->stk->next);
}
#endif
