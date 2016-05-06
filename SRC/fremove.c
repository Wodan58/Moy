/*
    module  : fremove.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
/* fremove.c */
PRIVATE void fremove_(void)
{
    ONEPARAM("fremove");
    STRING("fremove");
    if (OUTSIDE) {
	stk->next->u.num = !remove(stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	UNARY(BOOLEAN_NEWNODE, !remove(stk->u.str));
}
