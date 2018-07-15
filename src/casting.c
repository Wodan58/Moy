/*
    module  : casting.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef CASTING_X
#define CASTING_C

#ifdef NEW_VERSION
void do_casting(void)
{
    TRACE;
    (void)do_pop();
}
#else
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
    if (OUTSIDE) {
	stk->next->op = stk->op;
	POP(stk);
    } else
	GBINARY(stk->op, stk->next->u.ptr);
}
#endif
#endif
