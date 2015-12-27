/* getenv.c */
PRIVATE void getenv_()
{
    ONEPARAM("getenv");
    STRING("getenv");
    if (OUTSIDE)
	stk->u.str = getenv(stk->u.str);
    else
	UNARY(STRING_NEWNODE, getenv(stk->u.str));
}
