/*
    module  : body.c
    version : 1.6
    date    : 06/28/18
*/
#include "runtime.h"

/**
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
	stk->u.lis = dict_body(stk->u.num);
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, dict_body(stk->u.num));
#else
    POP(stk);
#endif
}
