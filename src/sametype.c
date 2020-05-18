/*
    module  : sametype.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

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
    stk->next->u.num = stk->op == stk->next->op;
    stk->next->op = BOOLEAN_;
    POP(stk);
}
#endif
