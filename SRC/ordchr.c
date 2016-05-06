/*
    module  : ordchr.c
    version : 1.2
    date    : 05/06/16
*/
/* ordchr.c */
PRIVATE void PROCEDURE(void)
{
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    if (OUTSIDE)
	stk->op = RESULTTYP;
    else
	stk = newnode(RESULTTYP, stk->u.ptr, stk->next);
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
