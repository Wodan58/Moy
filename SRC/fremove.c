/* fremove.c */
PRIVATE void fremove_()
{
    ONEPARAM("fremove");
    STRING("fremove");
    if (OUTSIDE) {
	stk->next->u.num = !remove(stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	UNARY(BOOLEAN_NEWNODE, !remove(stk->u.str));
}
