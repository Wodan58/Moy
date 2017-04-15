/*
    module  : body.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
PRIVATE void do_body(void)
{
#ifndef NCHECK
    if (optimizing)
	chg_history2(LIST_, USR_);
    COMPILE;
    ONEPARAM("body");
    USERDEF("body");
    if (OUTSIDE) {
	stk->u.lis = stk->u.ent->u.body;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, stk->u.ent->u.body);
#else
    POP(stk);
#endif
}
