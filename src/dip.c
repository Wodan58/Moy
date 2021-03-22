/*
    module  : dip.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef DIP_C
#define DIP_C

#ifndef OLD_RUNTIME
int put_dip(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* DIP */");
    fprintf(outfp, "Node temp = *env->stk; POP(env->stk);");
    compile(env, prog);
    fprintf(outfp, "DUPLICATE(&temp); }");
    return 1;
}
#endif

/**
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
PRIVATE void do_dip(pEnv env)
{
    Node *prog, temp;

#ifndef OLD_RUNTIME
    if (compiling && put_dip(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("dip");
    ONEQUOTE("dip");
    prog = env->stk->u.lis;
    POP(env->stk);
    temp = *env->stk;
    POP(env->stk);
    exeterm(env, prog);
    DUPLICATE(&temp);
}
#endif
