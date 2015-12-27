/* size.c */
PRIVATE void size_()
{
    size_t size = 0;

    ONEPARAM("size");
    switch (stk->op) {
    case SET_:
	{
	    int i;
	    for (i = 0; i < SETSIZE; i++)
		if (stk->u.set & (1 << i))
		    size++;
	    break;
	}
    case STRING_:
	size = strlen(stk->u.str);
	break;
    case LIST_:
	{
	    Node *cur;
	    for (cur = stk->u.lis; cur; cur = cur->next)
		size++;
	    break;
	}
    default:
	BADAGGREGATE("size");
    }
    if (OUTSIDE) {
	stk->u.num = size;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, size);
}
