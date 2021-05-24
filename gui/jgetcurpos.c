/*
    module  : jgetcurpos.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETCURPOS_C
#define JGETCURPOS_C

/**
jgetcurpos  :  obj  ->  position
Returns the position, in characters, of the text cursor.
*/
PRIVATE void do_jgetcurpos(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    env->stk->u.num = j_getcurpos(obj);
}
#endif
