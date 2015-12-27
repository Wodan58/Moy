/* ordchr.c */
PRIVATE void PROCEDURE()
{
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    if (OUTSIDE)
	stk->op = RESULTTYP;
    else
	stk = newnode(RESULTTYP, (Types) stk->u.num, stk->next);
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
