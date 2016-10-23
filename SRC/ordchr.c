/*
    module  : ordchr.c
    version : 1.3
    date    : 10/04/16
*/
/* ordchr.c */
PRIVATE void PROCEDURE(void)
{
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    if (OUTSIDE)
	stk->op = RESULTTYP;
    else
	GNULLARY(RESULTTYP, stk->u.ptr);
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
