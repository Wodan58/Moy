/*
    module  : bfloat.c
    version : 1.4
    date    : 04/08/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
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
