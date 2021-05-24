/*
    module  : jappendtext.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JAPPENDTEXT_C
#define JAPPENDTEXT_C

/**
jappendtext  :  obj text  ->
Appends the given text to the obj current text.
*/
PRIVATE void do_jappendtext(pEnv env)
{
    int obj;
    char *text;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    STRING(__func__);
    INTEGER2(__func__);
    text = env->stk->u.str;
    POP(env->stk);
    obj = env->stk->u.num;
    POP(env->stk);
    j_appendtext(obj, text);
}
#endif
