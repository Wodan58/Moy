/*
    module  : casting.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef CASTING_C
#define CASTING_C

/**
casting  :  X Y  ->  Z
Z takes the value from X and the type from Y.
*/
PRIVATE void do_casting(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("casting");
    stk->next->op = stk->op;
    POP(stk);
}
#endif
