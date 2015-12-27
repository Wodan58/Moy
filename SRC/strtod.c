/* strtod.c */
PRIVATE void strtod_()
{
    ONEPARAM("strtod");
    STRING("strtod");
    if (OUTSIDE) {
	stk->u.num = strtod(stk->u.str, 0);
	stk->op = FLOAT_;
    } else
	UNARY(FLOAT_NEWNODE, strtod(stk->u.str, 0));
}
