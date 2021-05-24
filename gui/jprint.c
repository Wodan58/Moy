/*
    module  : jprint.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPRINT_C
#define JPRINT_C

/**
jprint  :  obj  ->
Prints the component. With X-Windows all components have Motif-look. If
component is a printer, the actual page will be closed, and a new page will be
opened. The pages are not yet printed. To print all pages call jdispose.
*/
PRIVATE void do_jprint(pEnv env)
{
    int obj;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    obj = env->stk->u.num;
    POP(env->stk);
    j_print(obj);
}
#endif
