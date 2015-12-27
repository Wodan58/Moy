/* step.c */
PRIVATE void step_()
{
    Node *prog, *data, *cur;

    TWOPARAMS("step");
    ONEQUOTE("step");
    prog = stk->u.lis;
    POP(stk);
    data = stk;
    POP(stk);
    switch (data->op) {
    case LIST_:
	 {
	    for (cur = data->u.lis; cur; cur = cur->next) {
		DUPLICATE(cur);
		exeterm(prog);
	    }
	    break;
	}
    case STRING_:
	 {
	    char *str;
	    for (str = data->u.str; str && *str; str++) {
		PUSH(CHAR_, *str);
		exeterm(prog);
	    }
	    break;
	}
    case SET_:
	 {
	    int i;
	    long_t set = data->u.set;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    PUSH(INTEGER_, i);
		    exeterm(prog);
		}
	    break;
	}
    default:
	BADAGGREGATE("step");
    }
}
