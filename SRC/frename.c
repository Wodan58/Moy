/*
    module  : frename.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
frename  :  P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
/* frename.c */
PRIVATE void frename_(void)
{
    TWOPARAMS("frename");
    STRING("frename");
    STRING2("frename");
    if (OUTSIDE) {
	stk->next->u.num = !rename(stk->next->u.str, stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, !rename(stk->next->u.str, stk->u.str));
}
