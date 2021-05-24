/*
    module  : jfileselect.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JFILESELECT_C
#define JFILESELECT_C

/**
jfileselect  :  frame title filter filename  ->  filename
Opens a fileselector box with the preselected filename and the specified title
and returns the selected filename. filter specifies the Filename Filter. A
Fileselector can be used with output redirections via jconnect.
*/
PRIVATE void do_jfileselect(pEnv env)
{
    int frame;
    char *title, *filter, filename[MAXSTR];

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    FOURPARAMS(__func__);
    STRING(__func__);
    STRING2(__func__);
    STRING3(__func__);
    INTEGER4(__func__);
    strcpy(filename, env->stk->u.str);
    POP(env->stk);
    filter = env->stk->u.str;
    POP(env->stk);
    title = env->stk->u.str;
    POP(env->stk);
    frame = env->stk->u.num;
    j_fileselect(frame, title, filter, filename);
    env->stk->u.str = GC_strdup(filename);
    env->stk->op = STRING_;
}
#endif
