/*
    module  : app1.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef APP1_C
#define APP1_C

#ifndef OLD_RUNTIME
int put_app1(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    compile(env, prog);
    return 1;
}
#endif

/**
app1  :  X [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app1(pEnv env)
{
    Node *prog;

#ifndef OLD_RUNTIME
    if (compiling && put_app1(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("app1");
    ONEQUOTE("app1");
    prog = env->stk->u.lis;
    POP(env->stk);
    exeterm(env, prog);
}
#endif
