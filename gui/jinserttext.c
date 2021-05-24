/*
    module  : jinserttext.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JINSERTTEXT_C
#define JINSERTTEXT_C

/**
jinserttext  :  obj text pos  ->
Places additional text within the component at the given position pos.
*/
PRIVATE void do_jinserttext(pEnv env)
{
    char *text;
    int obj, pos;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    INTEGER(__func__);
    STRING2(__func__);
    INTEGER3(__func__);
    pos = env->stk->u.num;
    POP(env->stk);
    text = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_inserttext(obj, text, pos);
}
#endif
