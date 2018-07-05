/*
    module  : small_str.c
    version : 1.1
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_small_str(void)
{
    TRACE;
    stk[-1] = !stk[-1] || strlen((char *)stk[-1]) < 2;
}
#else
/**
small_str  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
PRIVATE void do_small_str(void)
{
    int small = 0;

#ifndef NCHECK
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("small");
    switch (stk->op) {
    case BOOLEAN_:
    case INTEGER_:
	small = stk->u.num < 2;
	break;
    case SET_:
	if (!stk->u.set)
	    small = 1;
	else {
	    int i = 0;
	    while (!(stk->u.set & (1 << i)))
		i++;
	    small = (stk->u.set & ~(1 << i)) == 0;
	}
	break;
    case STRING_:
	small = !stk->u.str || !*stk->u.str || !stk->u.str[1];
	break;
    case LIST_:
	small = !stk->u.lis || !stk->u.lis->next;
	break;
#ifndef NCHECK
    default:
	BADDATA("small");
#endif
    }
    if (OUTSIDE) {
	stk->u.num = small;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, small);
}
#endif
