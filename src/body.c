/*
    module  : body.c
    version : 1.14
    date    : 06/20/22
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
#ifdef COMPILING
    USERDEF("body");
    UNARY(LIST_NEWNODE, dict_body(env, env->stk->u.num));
#else
    UNARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(env->stk->u.proc, 0));
#endif
}
#endif
