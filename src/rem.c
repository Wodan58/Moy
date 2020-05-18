/*
    module  : rem.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef REM_C
#define REM_C

/**
rem  :  I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
PRIVATE void do_rem(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("rem");
    FLOAT2("rem");
#ifndef NCHECK
    if ((stk->op == FLOAT_ && !stk->u.dbl) ||
	(stk->op == INTEGER_ && !stk->u.num))
	execerror("non-zero operand", "rem");
#endif
    if (stk->next->op == FLOAT_)
	stk->next->u.dbl = fmod(stk->next->u.dbl, FLOATVAL);
    else if (stk->op == FLOAT_) {
	stk->next->u.dbl = fmod((double) stk->next->u.num, stk->u.dbl);
	stk->next->op = FLOAT_;
    } else
	stk->next->u.num %= stk->u.num;
    POP(stk);
}
#endif
