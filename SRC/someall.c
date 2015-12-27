/* someall.c */
PRIVATE void PROCEDURE()
{
    Operator op;
    char *str = 0;
    long_t set = 0;
    int i, result = INITIAL;
    Node *prog, *save, *list = 0, *cur;

    TWOPARAMS(NAME);
    ONEQUOTE(NAME);
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
	BADAGGREGATE(NAME);
    }
    POP(stk);
    save = stk;
    inside_critical++;
    switch (op) {
    case SET_:
	{
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    stk = INTEGER_NEWNODE(i, save);
		    exeterm(prog);
		    if (stk->u.num != INITIAL) {
			result = 1 - INITIAL;
			break;
		    }
		}
	    break;
	}
    case STRING_:
	{
	    for ( ; str && *str; str++)
		stk = CHAR_NEWNODE(*str, save);
		exeterm(prog);
		if (stk->u.num != INITIAL) {
		    result = 1 - INITIAL;
		    break;
		}
	    break;
	}
    case LIST_:
	{
	    for (cur = list; cur; cur = cur->next) {
		stk = newnode(cur->op, cur->u, save);
		exeterm(prog);
		if (stk->u.num != INITIAL) {
		    result = 1 - INITIAL;
		    break;
		}
	    }
	    break;
	}
    }
    if (--inside_critical == 0)
	tmp_release();
    stk = save;
    PUSH(BOOLEAN_, result);
}

#undef PROCEDURE
#undef NAME
#undef INITIAL
