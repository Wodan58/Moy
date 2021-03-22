/*
    module  : times.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef TIMES_C
#define TIMES_C

#ifndef OLD_RUNTIME
int put_times(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* TIMES */");
    fprintf(outfp, "int num = env->stk->u.num; POP(env->stk);");
    fprintf(outfp, "while (num--) {");
    compile(env, prog);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
times  :  N [P]  ->  ...
N times executes P.
*/
PRIVATE void do_times(pEnv env)
{
    int num;
    Node *prog;

#ifndef OLD_RUNTIME
    if (compiling && put_times(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("times");
    ONEQUOTE("times");
    INTEGER2("times");
    prog = env->stk->u.lis;
    POP(env->stk);
    num = env->stk->u.num;
    POP(env->stk);
    while (num--)
	exeterm(env, prog);
}
#endif
