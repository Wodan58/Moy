/*
    module  : map.c
    version : 1.9
    date    : 10/04/16
*/
#include "interp.h"

/*
map  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
/* map.c */
PRIVATE void map_(void)
{
    Node *prog, *cur = 0,
	 *root = 0, *last = 0, *save;
    int j;
#ifdef ARITY
    int d;
#endif

    TWOPARAMS("map");
    ONEQUOTE("map");
    prog = stk->u.lis;
    POP(stk);
    cur = stk;
    POP(stk);
#ifdef ARITY
    d = arity(prog);
#endif
    switch (cur->op) {
    case LIST_:
	 {
	    for (cur = cur->u.lis; cur; cur = cur->next) {
		save = stk;
#ifdef ARITY
		copy_(d);
#else
		CONDITION;
#endif
		DUPLICATE(cur);
		exeterm(prog);
#ifdef RUNTIME_CHECKS
		if (!stk)
		    execerror("non-empty stack", "map");
#endif
		if (!root)
		    last = root = heapnode(stk->op, stk->u.ptr, 0);
		else
		    last = last->next = heapnode(stk->op, stk->u.ptr, 0);
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
	    }
	    PUSH(LIST_, root);
	    break;
	}
    case STRING_:
	 {
	    char *str = cur->u.str, *result = strdup(str);
	    for (j = 0; str && *str; str++) {
		save = stk;
#ifdef ARITY
		copy_(d);
#else
		CONDITION;
#endif
		PUSH(CHAR_, *str);
		exeterm(prog);
		result[j++] = stk->u.num;
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
	    }
	    result[j] = 0;
	    PUSH(STRING_, result);
	    break;
	}
    case SET_:
	 {
	    long_t set = cur->u.set, result = 0;
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
		    result |= 1 << stk->u.num;
		    stk = save;
#ifndef ARITY
		    RELEASE;
#endif
		}
	    PUSH(SET_, result);
	    break;
	}
    default:
	BADAGGREGATE("map");
    }
}
