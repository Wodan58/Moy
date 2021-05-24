/*
    module  : jtextarea.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JTEXTAREA_C
#define JTEXTAREA_C

/**
jtextarea  :  obj rows columns  ->  event
Creates a new textarea component with the specified number of rows ans columns
and returns its event number.
*/
PRIVATE void do_jtextarea(pEnv env)
{
    int obj, rows, columns;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    INTEGER3(__func__);
    columns = env->stk->u.num;
    POP(env->stk);
    rows = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_textarea(obj, rows, columns);
}
#endif
