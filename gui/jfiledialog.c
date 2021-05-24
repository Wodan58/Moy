/*
    module  : jfiledialog.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JFILEDIALOG_C
#define JFILEDIALOG_C

/**
jfiledialog  :  frame title directory  ->  filename
Opens a filedialog box in the specified directory with the specified title and
returns the selected filename. If title contains "/S" the SAVE-filedialog will
be called. The substring "/S" will be removed.
*/
PRIVATE void do_jfiledialog(pEnv env)
{
    int frame;
    char *title, *directory, filename[MAXSTR];

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS(__func__);
    STRING(__func__);
    STRING2(__func__);
    INTEGER3(__func__);
    directory = env->stk->u.str;
    POP(env->stk);
    title = env->stk->u.str;
    POP(env->stk);
    frame = env->stk->u.num;
    j_filedialog(frame, title, directory, filename);
    env->stk->u.str = GC_strdup(filename);
    env->stk->op = STRING_;
}
#endif
