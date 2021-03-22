/*
    module  : body.c
    version : 1.13
    date    : 03/15/21
*/
#ifndef BODY_C
#define BODY_C

/**
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
PRIVATE void do_body(pEnv env)
{
    ONEPARAM("body");
#ifndef OLD_RUNTIME
    USERDEF("body");
    env->stk->u.lis = dict_body(env, env->stk->u.num);
    env->stk->op = LIST_;
#else
    POP(env->stk);
#endif
}
#endif
