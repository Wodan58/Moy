/*
    module  : split.c
    version : 1.11
    date    : 11/05/16
*/
#include "interp.h"

/*
split  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
/* split.c */
PRIVATE void split_(void)
{
    Node *prog, *save;
#ifdef ARITY
    int d;
#endif

    TWOPARAMS("split");
    ONEQUOTE("split");
    prog = stk->u.lis;
    POP(stk);
#ifdef ARITY
    d = arity(prog);
#endif
    switch (stk->op) {
    case SET_:
	{
	    int j;
	    long_t set, yes_set = 0, no_set = 0;

	    set = stk->u.set;
	    POP(stk);
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
		    if (stk->u.num) yes_set |= 1 << j;
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
	    char *str, *yesstring, *nostring;

	    str = stk->u.str;
	    POP(stk);
	    yesstring = strdup(str);
	    nostring = strdup(str);
	    for (; str && *str; str++) {
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
	    Node *list, *root = 0, *cur, *head = 0, *tail;

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
		if (stk->u.num)
		    if (!root)
			cur = root = heapnode(list->op, list->u.ptr, 0);
		    else
			cur = cur->next = heapnode(list->op, list->u.ptr, 0);
		else if (!head)
		    tail = head = heapnode(list->op, list->u.ptr, 0);
		else
		    tail = tail->next = heapnode(list->op, list->u.ptr, 0);
		stk = save;
#ifndef ARITY
		RELEASE;
#endif
	    }
	    PUSH(LIST_, root);
	    PUSH(LIST_, head);
	    break;
	}
    default:
	BADAGGREGATE("split");
    }
}
