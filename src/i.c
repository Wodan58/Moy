/*
    module  : i.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef I_C
#define I_C

#ifndef OLD_RUNTIME
int put_i(pEnv env)
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
i  :  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void do_i(pEnv env)
{
    Node *prog;

#ifndef OLD_RUNTIME
    if (compiling && put_i(env))
	return;
    COMPILE;
#endif
    ONEPARAM("i");
    ONEQUOTE("i");
    prog = env->stk->u.lis;
    POP(env->stk);
    exeterm(env, prog);
}
#endif
