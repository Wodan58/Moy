/* div.c */
PRIVATE void div_()
{
#ifdef BIT_32
    ldiv_t result;
#else
    lldiv_t result;
#endif

    TWOPARAMS("div");
    INTEGERS2("div");
    CHECKZERO("div");
#ifdef BIT_32
    result = ldiv(stk->next->u.num, stk->u.num);
#else
    result = lldiv(stk->next->u.num, stk->u.num);
#endif
    if (OUTSIDE) {
	stk->next->u.num = result.quot;
	stk->u.num = result.rem;
	return;
    }
    BINARY(INTEGER_NEWNODE, result.quot);
    NULLARY(INTEGER_NEWNODE, result.rem);
}
