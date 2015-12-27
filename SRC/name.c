/* name.c */
PRIVATE void name_()
{
    char *str;

    ONEPARAM("name");
    str = stk->op == USR_ ? stk->u.ent->name : opername(stk->op);
    if (OUTSIDE) {
	stk->u.str = str;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, str);
}
