/*
    module  : filter.c
    version : 1.10
    date    : 10/04/16
*/
#include "interp.h"

/*
filter  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
/* filter.c */
PRIVATE void filter_(void)
{
    Operator op;
    char *str = 0;
    long_t set = 0;
    Node *prog, *cur = 0,
	 *list = 0, *root = 0,
	 *save, *last = 0;
    int j, num;
#ifdef ARITY
    int d;
#endif

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
    }
    POP(stk);
#ifdef ARITY
    d = arity(prog);
#endif
    switch (op) {
    case SET_:
	{
	    long_t result = 0;

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
		    if (stk->u.num)
			result |= 1 << j;
		    stk = save;
#ifndef ARITY
		    RELEASE;
#endif
		}
	    PUSH(SET_, result);
	    break;
	}
    case STRING_:
	{
	    char *result = strdup(str);

	    for (j = 0; str && *str; str++) {
		save = stk;
#ifdef ARITY
		copy_(d);
#else
		CONDITION;
#endif
		PUSH(CHAR_, *str);
		exeterm(prog);
		if (stk->u.num)
		    result[j++] = *str;
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
	    }
	    result[j] = 0;
	    PUSH(STRING_, result);
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
		if (num) {
		    if (!root)
			last = root = heapnode(cur->op, cur->u.ptr, 0);
		    else
			last = last->next = heapnode(cur->op, cur->u.ptr, 0);
		}
	    }
	    PUSH(LIST_, root);
	    break;
	}
    default:
	BADAGGREGATE("filter");
    }
}
