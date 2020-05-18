/*
    module  : drop.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef DROP_C
#define DROP_C

/**
drop  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
PRIVATE void do_drop(void)
{
    int i, num;
    Node *node;
    ulong_t set;

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && AGGREGATE_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("drop");
    num = stk->u.num;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	node = stk->u.lis;
	while (num-- > 0 && node)
	    node = node->next;
	stk->u.lis = node;
	break;
    case STRING_:
	stk->u.str += num;
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & ((long_t)1 << i)) {
		if (num < 1)
		    set |= (long_t)1 << i;
		else
		    num--;
	    }
	stk->u.set = set;
	break;
    default:
	BADAGGREGATE("drop");
	break;
    }
}
#endif
