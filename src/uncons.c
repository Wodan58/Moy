/*
    module  : uncons.c
    version : 1.11
    date    : 07/06/18
*/
#ifdef RUNTIME
void do_uncons(void)
{
    code_t *cur;

    TRACE;
    if ((cur = (code_t *)stk[-1]) == 0) {
	stk[-1] = start_of_text;
	do_push(0);
    } else {
	stk[-1] = cur->num;
	do_push((node_t)cur->next);
    }
}
#else
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

#ifndef NCHECK
    if (compiling && stk && ((stk->op == LIST_ && stk->u.lis->op > USR_ &&
	stk->u.lis->op <= SYMBOL_) || stk->op == STRING_ || stk->op == SET_))
	;
    else
	COMPILE;
#endif
    ONEPARAM("uncons");
    switch (stk->op) {
    case LIST_:
#if 0
	CHECKEMPTYLIST(stk->u.lis, "uncons");
#endif
	if ((save = stk->u.lis) == 0) {
	    if (OUTSIDE)
		stk->u.num = stk->op = NOTHING_;
	    else
		GUNARY(NOTHING_, (void *)NOTHING_);
	    PUSH(LIST_, 0);
	} else {
	    if (OUTSIDE) {
		stk->op = stk->u.lis->op;
		stk->u = stk->u.lis->u;
	    } else
		GUNARY(stk->u.lis->op, stk->u.lis->u.ptr);
	    PUSH(LIST_, save->next);
	}
	break;
    case STRING_:
	str = stk->u.str;
	CHECKEMPTYSTRING(str, "uncons");
	if (OUTSIDE) {
	    stk->u.num = *str;
	    stk->op = CHAR_;
	} else
	    UNARY(CHAR_NEWNODE, *str);
	PUSH(STRING_, ++str);
	break;
    case SET_:
	set = stk->u.set;
	CHECKEMPTYSET(set, "uncons");
	while (!(set & (1 << i)))
	    i++;
	if (OUTSIDE) {
	    stk->u.num = i;
	    stk->op = INTEGER_;
	} else
	    UNARY(INTEGER_NEWNODE, i);
	PUSH(SET_, set & ~(1 << i));
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("uncons");
#endif
    }
}
#endif
