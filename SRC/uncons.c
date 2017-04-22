/*
    module  : uncons.c
    version : 1.6
    date    : 04/22/17
*/
#include "runtime.h"

/*
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
    unsigned op = 0, op1;

    if (optimizing && ((stk->op == LIST_ && stk->u.lis->op >= BOOLEAN_ &&
	stk->u.lis->op < USR_) || stk->op == STRING_ || stk->op == SET_))
	;
    else
	COMPILE;
    if (optimizing)
	op = pop_history(&op1);
    ONEPARAM("uncons");
#endif
    switch (stk->op) {
    case LIST_:
#ifndef NCHECK
	if (optimizing)
	    add_history(op1);
//	CHECKEMPTYLIST(stk->u.lis, "uncons");
#endif
	if ((save = stk->u.lis) == 0) {
	    if (OUTSIDE)
		stk->u.num = stk->op = DO_NOTHING;
	    else
		GUNARY(DO_NOTHING, (void *)DO_NOTHING);
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
#ifndef NCHECK
	if (optimizing)
	    add_history(CHAR_);
	CHECKEMPTYSTRING(str, "uncons");
#endif
	if (OUTSIDE) {
	    stk->u.num = *str;
	    stk->op = CHAR_;
	} else
	    UNARY(CHAR_NEWNODE, *str);
	PUSH(STRING_, ++str);
	break;
    case SET_:
	set = stk->u.set;
#ifndef NCHECK
	if (optimizing)
	    add_history(INTEGER_);
	CHECKEMPTYSET(set, "uncons");
#endif
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
#ifndef NCHECK
    if (optimizing)
	add_history2(op, op1);
#endif
}
