/*
    module  : setundeferror.c
    version : 1.11
    date    : 06/20/22
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
