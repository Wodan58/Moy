/*
    module  : jreplacetext.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JREPLACETEXT_C
#define JREPLACETEXT_C

/**
jreplacetext  :  obj text start end  ->
Replaces the text from starting position start to ending position end with the
given text.
*/
PRIVATE void do_jreplacetext(pEnv env)
{
    char *text;
    int obj, start, end;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    STRING3(__func__);
    INTEGER4(__func__);
    end = env->stk->u.num;
    POP(env->stk);
    start = env->stk->u.num;
    POP(env->stk);
    text = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_replacetext(obj, text, start, end);
}
#endif
