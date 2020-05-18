/*
    module  : bfloat.h
    version : 1.8
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    FLOAT2(NAME);
    stk->next->u.dbl = FUNC(FLOATVAL2, FLOATVAL);
    stk->next->op = FLOAT_;
    POP(stk);
}

#undef PROCEDURE
#undef NAME
#undef FUNC
