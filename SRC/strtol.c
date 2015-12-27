/* strtol.c */
PRIVATE void strtol_()
{
    int base;

    TWOPARAMS("strtol");
    INTEGER("strtol");
    base = stk->u.num;
    POP(stk);
    STRING("strtol");
    if (OUTSIDE) {
#ifdef BIT_32
	stk->u.num = strtol(stk->u.str, 0, base);
#else
	stk->u.num = strtoll(stk->u.str, 0, base);
#endif
	stk->op = INTEGER_;
	return;
    }
#ifdef BIT_32
    UNARY(INTEGER_NEWNODE, strtol(stk->u.str, 0, base));
#else
    UNARY(INTEGER_NEWNODE, strtoll(stk->u.str, 0, base));
#endif
}
