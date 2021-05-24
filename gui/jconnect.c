/*
    module  : jconnect.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JCONNECT_C
#define JCONNECT_C

/**
jconnect  :  hostname  ->  status
Connects a running JAPI kernel on host hostname.
*/
PRIVATE void do_jconnect(pEnv env)
{
    char *hostname;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    STRING(__func__);
    hostname = env->stk->u.str;
    env->stk->u.num = j_connect(hostname);
    env->stk->op = INTEGER_;
}
#endif
