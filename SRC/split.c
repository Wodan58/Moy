/* split.c */
PRIVATE void split_()
{
    int i, num;
    Operator op;
    char *str = 0;
    long_t set = 0;
    Node *prog, *cur = 0, *root = 0, *last = 0,
	 *save, *list = 0, *head = 0, *tail = 0;

    TWOPARAMS("split");
    ONEQUOTE("split");
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
	    long_t yes_set = 0, no_set = 0;

	    inside_critical++;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    stk = INTEGER_NEWNODE(i, save);
		    exeterm(prog);
		    if (stk->u.num)
			yes_set |= 1 << i;
		    else
			no_set |= 1 << i;
		}
	    if (--inside_critical == 0)
		tmp_release();

	    stk = save;
	    PUSH(SET_, yes_set);
	    PUSH(SET_, no_set);
	    break;
	}
    case STRING_:
	{
	    int yesptr = 0, noptr = 0;
	    char *yesstring, *nostring;
	    yesstring = GC_malloc(strlen(str) + 1);
	    nostring = GC_malloc(strlen(str) + 1);

	    inside_critical++;
	    for ( ; str && *str; str++) {
		stk = CHAR_NEWNODE(*str, save);
		exeterm(prog);
		if (stk->u.num)
		    yesstring[yesptr++] = *str;
		else
		    nostring[noptr++] = *str;
	    }
	    if (--inside_critical == 0)
		tmp_release();

	    yesstring[yesptr] = '\0';
	    nostring[noptr] = '\0';
	    stk = save;
	    PUSH(STRING_, yesstring);
	    PUSH(STRING_, nostring);
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

		if (num)
		    if (!root)
			last = root = newnode(cur->op, cur->u, 0);
		    else
			last = last->next = newnode(cur->op, cur->u, 0);
		else if (!head)
		    tail = head = newnode(cur->op, cur->u, 0);
		else
		    tail = tail->next = newnode(cur->op, cur->u, 0);
	    }
	    stk = save;
	    PUSH(LIST_, root);
	    PUSH(LIST_, head);
	    break;
	}
    }
}
