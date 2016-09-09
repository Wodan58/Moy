/*
    module  : map.c
    version : 1.3
    date    : 09/09/16
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
#ifdef RUNTIME_CHECKS
		if (!stk)
		    execerror("non-empty stack", "map");
#endif
		if (!root)
		    last = root = newnode(stk->op, stk->u.ptr, 0);
		else
		    last = last->next = newnode(stk->op, stk->u.ptr, 0);
	    }
	    stk = save;
	    PUSH(LIST_, root);
	    break;
	}
    case STRING_:
	 {
	    char *str = data->u.str, *result;
	    result = GC_strdup(str);
	    for ( ; str && *str; str++) {
		stk = save;
		CONDITION;
		PUSH(CHAR_, (long_t)*str);
		exeterm(prog);
		num = stk->u.num;
		RELEASE;
		result[i++] = (char)num;
	    }
	    stk = save;
	    PUSH(STRING_, result);
	    break;
	}
    case SET_:
	 {
	    long_t set = data->u.set, result = 0;
	    for (i = 0; i < _SETSIZE_; i++)
		if (set & (1 << i)) {
		    stk = save;
		    CONDITION;
		    PUSH(INTEGER_, (long_t)i);
		    exeterm(prog);
		    num = stk->u.num;
		    RELEASE;
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
