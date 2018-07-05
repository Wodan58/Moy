/*
    module  : setundeferror.c
    version : 1.6
    date    : 07/05/18
*/

/**
setundeferror  :  I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
PRIVATE void do_setundeferror(void)
{
    ONEPARAM("undeferror");
    NUMERICTYPE("undeferror");
    undeferror = stk->u.num;
    POP(stk);
}
