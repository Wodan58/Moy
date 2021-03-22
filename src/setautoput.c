/*
    module  : setautoput.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef SETAUTOPUT_C
#define SETAUTOPUT_C

/**
setautoput  :  I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
PRIVATE void do_setautoput(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("setautoput");
    NUMERICTYPE("setautoput");
    autoput = env->stk->u.num;
    POP(env->stk);
}
#endif
