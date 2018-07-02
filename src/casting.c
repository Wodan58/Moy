/*
    module  : casting.c
    version : 1.6
    date    : 07/02/18
*/

/**
casting  :  X Y  ->  Z
Z takes the value from X and the type from Y.
*/
PRIVATE void do_casting(void)
{
#ifndef NCHECK
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
