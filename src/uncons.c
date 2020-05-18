/*
    module  : uncons.c
    version : 1.15
    date    : 03/28/20
*/
#ifndef UNCONS_C
#define UNCONS_C

/**
uncons  :  A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
PRIVATE void do_uncons(void)
{
    char *str;
    int i = 0;
    Node *save;
    ulong_t set;

#ifndef OLD_RUNTIME
    if (compiling && stk && ((stk->op == LIST_ && stk->u.lis->op > USR_ &&
	stk->u.lis->op <= SYMBOL_) || stk->op == STRING_ || stk->op == SET_))
	;
    else
	COMPILE;
#endif
    ONEPARAM("uncons");
    switch (stk->op) {
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "uncons");
	save = stk->u.lis;
	stk->op = stk->u.lis->op;
	stk->u = stk->u.lis->u;
	PUSH(LIST_, save->next);
	break;
    case STRING_:
	str = stk->u.str;
	CHECKEMPTYSTRING(str, "uncons");
	stk->u.num = *str;
	stk->op = CHAR_;
	PUSH(STRING_, ++str);
	break;
    case SET_:
	set = stk->u.set;
	CHECKEMPTYSET(set, "uncons");
	while (!(set & ((long_t)1 << i)))
	    i++;
	stk->u.num = i;
	stk->op = INTEGER_;
	PUSH(SET_, set & ~((long_t)1 << i));
	break;
    default:
	BADAGGREGATE("uncons");
	break;
    }
}
#endif
