/*
    module  : jsetport.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JSETPORT_C
#define JSETPORT_C

/**
jsetport  :  port  ->
Replace the default port by port. This can be useful if the default port is
used by an other application, or if you want to start several independent
kernels on one machine. This function must be called before calling jstart.
*/
PRIVATE void do_jsetport(pEnv env)
{
    int port;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    port = env->stk->u.num;
    POP(env->stk);
    j_setport(port);
}
#endif
