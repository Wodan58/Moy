/*
    module  : jmeter.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JMETER_C
#define JMETER_C

/**
jmeter  :  obj title  ->  event
Creates a new pointer-instrument with the specified label title and returns its
event number. The meter has predefined values from 0 to 100. This can be
changed via jsetmin and jsetmax. A danger value is set to 80 and can be
justified with jsetdanger.
*/
PRIVATE void do_jmeter(pEnv env)
{
    int obj;
    char *title;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    title = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_meter(obj, title);
}
#endif
