/*
    module  : bfloat.c
    version : 1.3
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
    TWOPARAMS(NAME);
    FLOAT2(NAME);
#endif
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
