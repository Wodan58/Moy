/*
    module  : %M%
    version : %I%
    date    : %G%
*/
#include "runtime.h"

/*
pick  :  X Y Z 2  ->  X Y Z X
Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
PRIVATE void do_pick(void)
{
    int num;
    Node *look;
#ifndef NCHECK
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    TWOPARAMS("pick");
#endif
    num = stk->u.num;
    POP(stk);
    for (look = stk; num--; look = look->next)
	;
    DUPLICATE(look);
}
