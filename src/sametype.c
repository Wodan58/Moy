/*
    module  : sametype.c
    version : 1.7
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_sametype(void)
{
    TRACE;
    stk[-2] = stk[-2] == stk[-1];
    stk--;
}
#else
/**
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
PRIVATE void do_sametype(void)
{
#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("sametype");
    if (OUTSIDE) {
	stk->next->u.num = stk->op == stk->next->op;
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, stk->op == stk->next->op);
}
#endif
