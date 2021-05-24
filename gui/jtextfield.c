/*
    module  : jtextfield.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JTEXTFIELD_C
#define JTEXTFIELD_C

/**
jtextfield  :  obj columns  ->  event
Creates a new textfield component with the specified number of columns and
returns its event number.
*/
PRIVATE void do_jtextfield(pEnv env)
{
    int obj, columns;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    columns = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_textfield(obj, columns);
}
#endif
