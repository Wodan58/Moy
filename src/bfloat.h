/*
    module  : bfloat.h
    version : 1.7
    date    : 07/15/18
*/
PRIVATE void PROCEDURE(void)
{
#ifdef NEW_RUNTIME
    float dbl1, dbl2;

    TRACE;
    memcpy(&dbl1, &stk[-2], sizeof(float));
    memcpy(&dbl2, &stk[-1], sizeof(float));
    dbl1 = FUNC(dbl1, dbl2);
    memcpy(&stk[-2], &dbl1, sizeof(node_t));
    (void)do_pop();
#else
#ifndef OLD_RUNTIME
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
#endif
}

#undef PROCEDURE
#undef NAME
#undef FUNC
