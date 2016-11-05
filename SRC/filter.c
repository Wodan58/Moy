/*
    module  : filter.c
    version : 1.11
    date    : 11/05/16
*/
#include "interp.h"

/*
filter  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
/* filter.c */
PRIVATE void filter_(void)
{
    int j;
    Node *prog, *save;
#ifdef ARITY
    int d;
#endif

    TWOPARAMS("filter");
    ONEQUOTE("filter");
    prog = stk->u.lis;
    POP(stk);
#ifdef ARITY
    d = arity(prog);
#endif
    switch (stk->op) {
    case SET_:
	{
	    long_t set, result = 0;

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
	    char *str, *result;

	    str = stk->u.str;
	    POP(stk);
	    result = strdup(str);
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
	    Node *list, *root = 0, *cur;

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
		if (stk->u.num) {
		    if (!root)
			cur = root = heapnode(list->op, list->u.ptr, 0);
		    else
			cur = cur->next = heapnode(list->op, list->u.ptr, 0);
		}
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
	    }
	    PUSH(LIST_, root);
	    break;
	}
    default:
	BADAGGREGATE("filter");
    }
}
