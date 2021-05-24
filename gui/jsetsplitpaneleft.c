/*
    module  : 
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETSPLITPANELEFT_C
#define JSETSPLITPANELEFT_C

/**
jsetsplitpaneleft  :  frame title  ->
Create a split pane with title text.
*/
PRIVATE void do_jsetsplitpaneleft(pEnv env)
{
    int frame, title;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS(__func__);
    INTEGER(__func__);
    INTEGER2(__func__);
    title = env->stk->u.num;
    POP(env->stk);
    frame = env->stk->u.num;
    POP(env->stk);
    j_setsplitpaneleft(frame, title);
}
#endif
