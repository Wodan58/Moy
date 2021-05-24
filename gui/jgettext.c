/*
    module  : jgettext.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETTEXT_C
#define JGETTEXT_C

/**
jgettext  :  obj  ->  text
Returns the component's text or label.
*/
PRIVATE void do_jgettext(pEnv env)
{
    int obj;
    char text[MAXSTR];

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    j_gettext(obj, text);
    env->stk->u.str = GC_strdup(text);
    env->stk->op = STRING_;
}
#endif
