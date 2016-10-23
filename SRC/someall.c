/*
    module  : someall.c
    version : 1.7
    date    : 10/04/16
*/
/* someall.c */
PRIVATE void PROCEDURE(void)
{
    Operator op;
    char *str = 0;
    long_t set = 0;
    Node *prog, *save, *list = 0, *cur;
    int i, num = INITIAL;
#ifdef ARITY
    int d;
#endif

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
    }
    POP(stk);
#ifdef ARITY
    d = arity(prog);
#endif
    switch (op) {
    case SET_:
	{
	    for (i = 0; i < _SETSIZE_; i++)
		if (set & (1 << i)) {
		    save = stk;
#ifdef ARITY
		    copy_(d);
#else
		    CONDITION;
#endif
		    PUSH(INTEGER_, i);
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
	    for ( ; str && *str; str++) {
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
	    for (cur = list; cur; cur = cur->next) {
		save = stk;
#ifdef ARITY
		copy_(d);
#else
		CONDITION;
#endif
		DUPLICATE(cur);
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
