/*
    module  : someall.c
    version : 1.8
    date    : 11/05/16
*/
/* someall.c */
PRIVATE void PROCEDURE(void)
{
    Node *prog, *save;
    int j, num = INITIAL;
#ifdef ARITY
    int d;
#endif

    TWOPARAMS(NAME);
    ONEQUOTE(NAME);
    prog = stk->u.lis;
    POP(stk);
#ifdef ARITY
    d = arity(prog);
#endif
    switch (stk->op) {
    case SET_:
	{
	    long_t set;

	    set = stk->u.set;
	    POP(stk);
	    for (j = 0; j < _SETSIZE_; j++)
		if (set & (1 << j)) {
		    save = stk;
#ifdef ARITY
		    copy_(d);
#else
		    CONDITION;
#endif
		    PUSH(INTEGER_, j);
		    exeterm(prog);
		    num = stk->u.num;
		    stk = save;
#ifndef ARITY
		    RELEASE;
#endif
		    if (num != INITIAL)
			break;
		}
	    break;
	}
    case STRING_:
	{
	    char *str;

	    str = stk->u.str;
	    POP(stk);
	    for (; str && *str; str++) {
		save = stk;
#ifdef ARITY
		copy_(d);
#else
		CONDITION;
#endif
		PUSH(CHAR_, *str);
		exeterm(prog);
		num = stk->u.num;
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
		if (num != INITIAL)
		    break;
	    }
	    break;
	}
    case LIST_:
	{
	    Node *list;

	    list = stk->u.lis;
	    POP(stk);
	    for (; list; list = list->next) {
		save = stk;
#ifdef ARITY
		copy_(d);
#else
		CONDITION;
#endif
		DUPLICATE(list);
		exeterm(prog);
		num = stk->u.num;
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
		if (num != INITIAL)
		    break;
	    }
	    break;
	}
    default:
	BADAGGREGATE(NAME);
    }
    PUSH(BOOLEAN_, num);
}

#undef PROCEDURE
#undef NAME
#undef INITIAL
