/*
    module  : take.c
    version : 1.12
    date    : 05/18/19
*/
#ifndef TAKE_X
#define TAKE_C

#ifdef NEW_RUNTIME
void do_take(void)
{
    int num;
    code_t *list, *root = 0, *cur, *last;

    TRACE;
    num = do_pop();
    if (num < 1) {
	stk[-1] = 0;
	return;
    }
    for (list = (code_t *)stk[-1]; list && num-- > 0; list = list->next) {
	cur = joy_code();
	cur->num = list->num;
	if (!root)
	    last = root = cur;
	else
	    last = last->next = cur;
    }
    stk[-1] = (node_t)root;
}
#else
/**
take  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
PRIVATE void do_take(void)
{
    char *str;
    int i, num;
    ulong_t set;
    Node *root = 0, *cur, *last;

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && AGGREGATE_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("take");
    num = stk->u.num;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	if (num < 1) {
	    if (OUTSIDE)
		stk->u.lis = 0;
	    else
		UNARY(LIST_NEWNODE, 0);
	} else {
	    for (cur = stk->u.lis; cur && num-- > 0; cur = cur->next)
		if (!root)
		    last = root = newnode(cur->op, cur->u.ptr, 0);
		else
		    last = last->next = newnode(cur->op, cur->u.ptr, 0);
	    if (OUTSIDE)
		stk->u.lis = root;
	    else
		UNARY(LIST_NEWNODE, root);
	}
	break;
    case STRING_:
	str = ck_malloc_sec(num + 1);
	strncpy(str, stk->u.str, num);
	str[num] = 0;
	if (OUTSIDE)
	    stk->u.str = str;
	else
	    UNARY(STRING_NEWNODE, str);
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & (1 << i)) {
		if (num-- > 0)
		    set |= 1 << i;
		else
		    break;
	    }
	if (OUTSIDE)
	    stk->u.set = set;
	else
	    UNARY(SET_NEWNODE, set);
	break;
    default:
	BADAGGREGATE("take");
	break;
    }
}
#endif
#endif
