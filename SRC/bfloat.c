/*
    module  : bfloat.c
    version : 1.2
    date    : 05/06/16
*/
/* bfloat.c */
PRIVATE void PROCEDURE(void)
{
    TWOPARAMS(NAME);
    FLOAT2(NAME);
    if (OUTSIDE) {
	stk->next->u.dbl = FUNC(FLOATVAL2, FLOATVAL);
	stk->next->op = FLOAT_;
    } else
	BINARY(FLOAT_NEWNODE, FUNC(FLOATVAL2, FLOATVAL));
}

#undef PROCEDURE
#undef NAME
#undef FUNC
