/*
    module  : setundeferror.c
    version : 1.2
    date    : 03/12/17
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
    COMPILE;
    ONEPARAM("undeferror");
    NUMERICTYPE("undeferror");
#endif
    undeferror = stk->u.num;
    POP(stk);
}
