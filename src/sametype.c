/*
    module  : sametype.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef SAMETYPE_X
#define SAMETYPE_C

#ifdef NEW_RUNTIME
void do_sametype(void)
{
    TRACE;
    stk[-2] = stk[-2] == stk[-1];
    (void)do_pop();
}
#else
/**
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
PRIVATE void do_sametype(void)
{
#ifndef OLD_RUNTIME
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
#endif
