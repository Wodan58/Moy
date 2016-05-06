/*
    module  : filter.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
filter  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
/* filter.c */
PRIVATE void filter_(void)
{
    int i, num;
    Operator op;
    char *str = 0;
    long_t set = 0;
    Node *prog, *cur = 0,
	 *list = 0, *root = 0,
	 *save, *last = 0;

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
    save = stk;
    switch (op) {
    case SET_:
	{
	    long_t result = 0;

	    CONDITION;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    stk = INTEGER_NEWNODE(i, save);
		    exeterm(prog);
		    if (stk->u.num)
			result |= 1 << i;
		}
	    RELEASE;
	    stk = save;
	    PUSH(SET_, result);
	    break;
	}
    case STRING_:
	{
	    char *result = GC_strdup(str);

	    CONDITION;
	    for (i = 0; str && *str; str++) {
		stk = CHAR_NEWNODE(*str, save);
		exeterm(prog);
		if (stk->u.num)
		    result[i++] = *str;
	    }
	    RELEASE;
	    result[i] = '\0';
	    stk = save;
	    PUSH(STRING_, result);
	    break;
	}
    case LIST_:
	{
	    for (cur = list; cur; cur = cur->next) {
		CONDITION;
		stk = newnode(cur->op, cur->u.ptr, save);
		exeterm(prog);
		num = stk->u.num;
		RELEASE;
		if (num) {
		    if (!root)
			last = root = newnode(cur->op, cur->u.ptr, 0);
		    else
			last = last->next = newnode(cur->op, cur->u.ptr, 0);
		}
	    }
	    stk = save;
	    PUSH(LIST_, root);
	    break;
	}
    default:
	BADAGGREGATE("filter");
    }
}
