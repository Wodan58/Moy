/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETSPLITPANERIGHT_C
#define JSETSPLITPANERIGHT_C

/**
jsetsplitpaneright  :  frame text  ->
Create a split pane with title text.
*/
PRIVATE void do_jsetsplitpaneright(pEnv env)
{
    int frame, text;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    text = env->stk->u.num;
    POP(env->stk);
    frame = env->stk->u.num;
    POP(env->stk);
    j_setsplitpaneright(frame, text);
}
#endif
