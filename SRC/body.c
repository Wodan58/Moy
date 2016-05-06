/*
    module  : body.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
/* body.c */
PRIVATE void body_(void)
{
    ONEPARAM("body");
    USERDEF("body");
    if (OUTSIDE) {
	stk->u.lis = stk->u.ent->u.body;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, stk->u.ent->u.body);
}
