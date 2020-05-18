/*
    module  : take.c
    version : 1.13
    date    : 03/28/20
*/
#ifndef TAKE_C
#define TAKE_C

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
	if (num < 1)
	    stk->u.lis = 0;
	else {
	    for (cur = stk->u.lis; cur && num-- > 0; cur = cur->next)
		if (!root)
		    last = root = newnode(cur->op, cur->u.ptr, 0);
		else
		    last = last->next = newnode(cur->op, cur->u.ptr, 0);
	    stk->u.lis = root;
	}
	break;
    case STRING_:
	str = ck_malloc_sec(num + 1);
	strncpy(str, stk->u.str, num);
	str[num] = 0;
	stk->u.str = str;
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & ((long_t)1 << i)) {
		if (num-- > 0)
		    set |= (long_t)1 << i;
		else
		    break;
	    }
	stk->u.set = set;
	break;
    default:
	BADAGGREGATE("take");
	break;
    }
}
#endif
