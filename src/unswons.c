/*
    module  : unswons.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef UNSWONS_C
#define UNSWONS_C

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
	stk->u.lis = stk->u.lis->next;
	DUPLICATE(save);
	break;
    case STRING_:
	str = stk->u.str;
	CHECKEMPTYSTRING(str, "unswons");
	stk->u.str = str + 1;
	PUSH(CHAR_, (long_t)*str);
	break;
    case SET_:
	set = stk->u.set;
	CHECKEMPTYSET(set, "unswons");
	while (!(set & ((long_t)1 << i)))
	    i++;
	stk->u.set = set & ~((long_t)1 << i);
	PUSH(INTEGER_, i);
	break;
    default:
	BADAGGREGATE("unswons");
	break;
    }
}
#endif
