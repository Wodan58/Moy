/*
    module  : split.c
    version : 1.10
    date    : 10/04/16
*/
#include <assert.h>
#include "interp.h"

/*
split  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
/* split.c */
PRIVATE void split_(void)
{
    Operator op;
    char *str = 0;
    long_t set = 0;
    int j, num;
    Node *prog, *cur = 0, *root = 0, *last = 0,
	 *save, *list = 0, *head = 0, *tail = 0;
#ifdef ARITY
    int d;
#endif

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
#ifdef ARITY
    d = arity(prog);
#endif
    switch (op) {
    case SET_:
	{
	    long_t yes_set = 0, no_set = 0;
	    for (j = 0; j < _SETSIZE_; j++) {
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
			yes_set |= 1 << j;
		    else
			no_set |= 1 << j;
		    stk = save;
#ifndef ARITY
		    RELEASE;
#endif
		}
	    }
	    PUSH(SET_, yes_set);
	    PUSH(SET_, no_set);
	    break;
	}
    case STRING_:
	{
	    int yesptr = 0, noptr = 0;
	    char *yesstring = strdup(str),
		 *nostring = strdup(str);
	    for ( ; str && *str; str++) {
		save = stk;
#ifdef ARITY
		copy_(d);
#else
		CONDITION;
#endif
		PUSH(CHAR_, *str);
		exeterm(prog);
		if (stk->u.num)
		    yesstring[yesptr++] = *str;
		else
		    nostring[noptr++] = *str;
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
	    }
	    yesstring[yesptr] = '\0';
	    nostring[noptr] = '\0';
	    PUSH(STRING_, yesstring);
	    PUSH(STRING_, nostring);
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
		if (num)
		    if (!root)
			last = root = heapnode(cur->op, cur->u.ptr, 0);
		    else
			last = last->next = heapnode(cur->op, cur->u.ptr, 0);
		else if (!head)
		    tail = head = heapnode(cur->op, cur->u.ptr, 0);
		else
		    tail = tail->next = heapnode(cur->op, cur->u.ptr, 0);
	    }
	    PUSH(LIST_, root);
	    PUSH(LIST_, head);
	    break;
	}
    default:
	BADAGGREGATE("split");
    }
}
