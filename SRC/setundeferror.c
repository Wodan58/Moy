/*
    module  : setundeferror.c
    version : 1.3
    date    : 04/09/17
*/
#include "runtime.h"

/*
setundeferror  :  I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
PRIVATE void do_setundeferror(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("undeferror");
    NUMERICTYPE("undeferror");
#endif
    undeferror = stk->u.num;
    POP(stk);
}
