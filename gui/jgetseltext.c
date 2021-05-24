/*
    module  : jgetseltext.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JGETSELTEXT_C
#define JGETSELTEXT_C

/**
jgetseltext  :  obj  ->  text
Returns the currently selected text of component obj.
*/
PRIVATE void do_jgetseltext(pEnv env)
{
    int obj;
    char text[MAXSTR];

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    obj = env->stk->u.num;
    j_getseltext(obj, text);
    env->stk->u.str = GC_strdup(text);
    env->stk->op = STRING_;
}
#endif
