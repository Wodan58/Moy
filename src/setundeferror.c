/*
    module  : setundeferror.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef SETUNDEFERROR_X
#define SETUNDEFERROR_C

#ifdef NEW_RUNTIME
void do_setundeferror(void)
{
    TRACE;
    undeferror = do_pop();
}
#else
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
#endif
