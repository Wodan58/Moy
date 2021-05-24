/*
    module  : jsetcursor.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETCURSOR_C
#define JSETCURSOR_C

/**
jsetcursor  :  obj cursor  ->
Changes the component's obj cursor to the specified cursor.
*/
PRIVATE void do_jsetcursor(pEnv env)
{
    int obj, cursor;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    cursor = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setcursor(obj, cursor);
}
#endif
