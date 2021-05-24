/*
    module  : jframe.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JFRAME_C
#define JFRAME_C

/**
jframe  :  label  ->  event
Creates a new frame component with the specified label and returns its event
number.
*/
PRIVATE void do_jframe(pEnv env)
{
    char *label;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    STRING(__func__);
    label = env->stk->u.str;
    env->stk->u.num = j_frame(label);
    env->stk->op = INTEGER_;
}
#endif
