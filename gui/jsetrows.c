/*
    module  : jsetrows.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETROWS_C
#define JSETROWS_C

/**
jsetrows  :  obj rows  ->
Sets the number of rows for obj to rows.
*/
PRIVATE void do_jsetrows(pEnv env)
{
    int obj, rows;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    rows = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_setrows(obj, rows);
}
#endif
