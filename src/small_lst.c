/*
    module  : small_lst.c
    version : 1.3
    date    : 07/15/18
*/
#ifndef SMALL_LST_X
#define SMALL_LST_C

#ifdef NEW_RUNTIME
void do_small_lst(void)
{
    code_t *cur;

    TRACE;
    cur = (code_t *)stk[-1];
    stk[-1] = !cur || !cur->next;
}
#else
/**
small_lst  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
PRIVATE void do_small_lst(void)
{
    int small = 0;

#ifndef OLD_RUNTIME
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
    default:
	BADDATA("small");
	break;
    }
    if (OUTSIDE) {
	stk->u.num = small;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, small);
}
#endif
#endif
