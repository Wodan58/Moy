/*
    module  : drop.c
    version : 1.7
    date    : 07/02/18
*/

/**
drop  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
PRIVATE void do_drop(void)
{
    int i, num;
    Node *node;
    ulong_t set;

#ifndef NCHECK
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
	if (OUTSIDE)
	    stk->u.lis = node;
	else
	    UNARY(LIST_NEWNODE, node);
	break;
    case STRING_:
	if (OUTSIDE)
	    stk->u.str += num;
	else
	    UNARY(STRING_NEWNODE, (stk->u.str + num));
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & (1 << i)) {
		if (num < 1)
		    set |= 1 << i;
		else
		    num--;
	    }
	if (OUTSIDE)
	    stk->u.set = set;
	else
	    UNARY(SET_NEWNODE, set);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("drop");
#endif
    }
}
