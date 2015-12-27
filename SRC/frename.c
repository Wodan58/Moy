/* frename.c */
PRIVATE void frename_()
{
    TWOPARAMS("frename");
    STRING("frename");
    STRING2("frename");
    if (OUTSIDE) {
	stk->next->u.num = !rename(stk->next->u.str, stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, !rename(stk->next->u.str, stk->u.str));
}
