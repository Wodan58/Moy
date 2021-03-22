/*
    module  : setundeferror.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef SETUNDEFERROR_C
#define SETUNDEFERROR_C

/**
setundeferror  :  I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
PRIVATE void do_setundeferror(pEnv env)
{
    ONEPARAM("undeferror");
    NUMERICTYPE("undeferror");
    undeferror = env->stk->u.num;
    POP(env->stk);
}
#endif
