/*
    module  : split.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
split  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
/* split.c */
PRIVATE void split_(void)
{
    int i, num;
    Operator op;
    char *str = 0;
    long_t set = 0;
    Node *prog, *cur = 0, *root = 0, *last = 0,
	 *save, *list = 0, *head = 0, *tail = 0;

    TWOPARAMS("split");
    ONEQUOTE("split");
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
	    long_t yes_set = 0, no_set = 0;
	    CONDITION;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    stk = INTEGER_NEWNODE(i, save);
		    exeterm(prog);
		    if (stk->u.num)
			yes_set |= 1 << i;
		    else
			no_set |= 1 << i;
		}
	    RELEASE;
	    stk = save;
	    PUSH(SET_, yes_set);
	    PUSH(SET_, no_set);
	    break;
	}
    case STRING_:
	{
	    int yesptr = 0, noptr = 0;
	    char *yesstring, *nostring;
	    yesstring = GC_strdup(str);
	    nostring = GC_strdup(str);
	    CONDITION;
	    for ( ; str && *str; str++) {
		stk = CHAR_NEWNODE(*str, save);
		exeterm(prog);
		if (stk->u.num)
		    yesstring[yesptr++] = *str;
		else
		    nostring[noptr++] = *str;
	    }
	    RELEASE;
	    yesstring[yesptr] = '\0';
	    nostring[noptr] = '\0';
	    stk = save;
	    PUSH(STRING_, yesstring);
	    PUSH(STRING_, nostring);
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
		if (num)
		    if (!root)
			last = root = newnode(cur->op, cur->u.ptr, 0);
		    else
			last = last->next = newnode(cur->op, cur->u.ptr, 0);
		else if (!head)
		    tail = head = newnode(cur->op, cur->u.ptr, 0);
		else
		    tail = tail->next = newnode(cur->op, cur->u.ptr, 0);
	    }
	    stk = save;
	    PUSH(LIST_, root);
	    PUSH(LIST_, head);
	    break;
	}
    default:
	BADAGGREGATE("filter");
    }
}
