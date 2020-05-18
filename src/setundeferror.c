/*
    module  : setundeferror.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef SETUNDEFERROR_C
#define SETUNDEFERROR_C

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
#endif
