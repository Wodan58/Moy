/*
    module  : bfloat.h
    version : 1.5
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    FLOAT2(NAME);
    if (OUTSIDE) {
	stk->next->u.dbl = FUNC(FLOATVAL2, FLOATVAL);
	stk->next->op = FLOAT_;
	POP(stk);
    } else
	BINARY(FLOAT_NEWNODE, FUNC(FLOATVAL2, FLOATVAL));
}

#undef PROCEDURE
#undef NAME
#undef FUNC
