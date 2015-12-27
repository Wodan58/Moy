/* body.c */
PRIVATE void body_()
{
    ONEPARAM("body");
    USERDEF("body");
    if (OUTSIDE) {
	stk->u.lis = stk->u.ent->u.body;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, stk->u.ent->u.body);
}
