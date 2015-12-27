/* filter.c */
PRIVATE void filter_()
{
    int i, num;
    Operator op;
    char *str = 0;
    long_t set = 0;
    Node *prog, *cur = 0,
	 *list = 0, *root = 0,
	 *save, *last = 0;

    TWOPARAMS("filter");
    ONEQUOTE("filter");
    prog = stk->u.lis;
    POP(stk);
    switch (op = stk->op) {
    case SET_:
	set = stk->u.set;
	break;
    case STRING_:
	str = stk->u.str;
	break;
    case LIST_:
	list = stk->u.lis;
	break;
    default:
	BADAGGREGATE("filter");
    }
    POP(stk);
    save = stk;
    switch (op) {
    case SET_:
	{
	    long_t result = 0;

	    inside_critical++;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    stk = INTEGER_NEWNODE(i, save);
		    exeterm(prog);
		    if (stk->u.num)
			result |= 1 << i;
		}
	    if (--inside_critical == 0)
		tmp_release();

	    stk = save;
	    PUSH(SET_, result);
	    break;
	}
    case STRING_:
	{
	    char *result = GC_malloc(strlen(str) + 1);

	    inside_critical++;
	    for (i = 0; str && *str; str++) {
		stk = CHAR_NEWNODE(*str, save);
		exeterm(prog);
		if (stk->u.num)
		    result[i++] = *str;
	    }
	    if (--inside_critical == 0)
		tmp_release();

	    result[i] = '\0';
	    stk = save;
	    PUSH(STRING_, result);
	    break;
	}
    case LIST_:
	{
	    for (cur = list; cur; cur = cur->next) {

		inside_critical++;
		stk = newnode(cur->op, cur->u, save);
		exeterm(prog);
		num = stk->u.num;
		if (--inside_critical == 0)
		    tmp_release();

		if (num) {
		    if (!root)
			last = root = newnode(cur->op, cur->u, 0);
		    else
			last = last->next = newnode(cur->op, cur->u, 0);
		}
	    }
	    stk = save;
	    PUSH(LIST_, root);
	    break;
	}
    }
}
