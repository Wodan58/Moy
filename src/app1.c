/*
    module  : app1.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef APP1_C
#define APP1_C

/**
app1  :  X [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app1(pEnv env)
{
    Node *prog;

    TWOPARAMS("app1"); /* i takes only 1 parameter */
    ONEQUOTE("app1");
    prog = env->stk->u.lis;
    POP(env->stk);
    exeterm(env, prog);
}
#endif
