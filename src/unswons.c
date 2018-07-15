/*
    module  : unswons.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef UNSWONS_X
#define UNSWONS_C

#ifdef NEW_RUNTIME
void do_unswons(void)
{
    code_t *cur;

    TRACE;
    cur = (code_t *)stk[-1];
    stk[-1] = (node_t)cur->next;
    do_push(cur->num);
}
#else
/**
unswons  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
PRIVATE void do_unswons(void)
{
    char *str;
    int i = 0;
    Node *save;
    ulong_t set;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("unswons");
    switch (stk->op) {
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "unswons");
	save = stk->u.lis;
	if (OUTSIDE)
	    stk->u.lis = stk->u.lis->next;
	else
	    UNARY(LIST_NEWNODE, stk->u.lis->next);
	DUPLICATE(save);
	break;
    case STRING_:
	str = stk->u.str;
	CHECKEMPTYSTRING(str, "unswons");
	if (OUTSIDE)
	    stk->u.str = str + 1;
	else
	    UNARY(STRING_NEWNODE, (str + 1));
	PUSH(CHAR_, (long_t)*str);
	break;
    case SET_:
	set = stk->u.set;
	CHECKEMPTYSET(set, "unswons");
	while (!(set & (1 << i)))
	    i++;
	if (OUTSIDE)
	    stk->u.set = set & ~(1 << i);
	else
	    UNARY(SET_NEWNODE, set & ~(1 << i));
	PUSH(INTEGER_, i);
	break;
    default:
	BADAGGREGATE("unswons");
	break;
    }
}
#endif
#endif
