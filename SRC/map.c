/* map.c */
PRIVATE void map_()
{
    Node *prog, *cur = 0,
	 *data, *root = 0,
	 *save, *last = 0;
    int i = 0, num;

    TWOPARAMS("map");
    ONEQUOTE("map");
    prog = stk->u.lis;
    POP(stk);
    data = stk;
    POP(stk);
    save = stk;
    switch (data->op) {
    case LIST_:
	 {
	    for (cur = data->u.lis; cur; cur = cur->next) {
		stk = save;

		inside_condition++;
		DUPLICATE(cur);
		exeterm(prog);
		inside_condition--;

		if (!stk)
		    execerror("non-empty stack", "map");
		if (!root)
		    last = root = newnode(stk->op, stk->u, 0);
		else
		    last = last->next = newnode(stk->op, stk->u, 0);
	    }
	    stk = save;
	    PUSH(LIST_, root);
	    break;
	}
    case STRING_:
	 {
	    char *str, *result;
	    result = GC_malloc(strlen(data->u.str) + 1);
	    for (str = data->u.str; str && *str; str++) {
		stk = save;

		inside_critical++;
		PUSH(CHAR_, *str);
		exeterm(prog);
		num = stk->u.num;
		if (--inside_critical == 0)
		    tmp_release();

		result[i++] = num;
	    }
	    stk = save;
	    PUSH(STRING_, result);
	    break;
	}
    case SET_:
	 {
	    long_t set = data->u.set, result = 0;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    stk = save;

		    inside_critical++;
		    PUSH(INTEGER_, i);
		    exeterm(prog);
		    num = stk->u.num;
		    if (--inside_critical == 0)
			tmp_release();

		    result |= 1 << num;
		}
	    stk = save;
	    PUSH(SET_, result);
	    break;
	}
    default:
	BADAGGREGATE("map");
    }
}
