/*
    module  : jsevensegment.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSEVENSEGMENT_C
#define JSEVENSEGMENT_C

/**
jsevensegment  :  obj color  ->  event
Creates a new sevensegment display and returns its event number. The color
can be one of the predefined colors (e.g. J_RED, J_GREEN).
*/
PRIVATE void do_jsevensegment(pEnv env)
{
    int obj, color;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    color = env->stk->u.num;
    POP(env->stk);
    obj = env->stk->u.num;
    env->stk->u.num = j_sevensegment(obj, color);
}
#endif
