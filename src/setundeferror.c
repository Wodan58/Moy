/*
    module  : setundeferror.c
    version : 1.5
    date    : 07/02/18
*/

/**
setundeferror  :  I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
PRIVATE void do_setundeferror(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("undeferror");
    NUMERICTYPE("undeferror");
    undeferror = stk->u.num;
    POP(stk);
}
