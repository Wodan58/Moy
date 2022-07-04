/*
    module  : times.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef TIMES_C
#define TIMES_C

/**
times  :  N [P]  ->  ...
N times executes P.
*/
#ifdef COMPILING
void put_times(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* TIMES */");
    fprintf(outfp, "int num = env->stk->u.num; POP(env->stk);");
    fprintf(outfp, "while (num--) {");
    compile(env, prog);
    fprintf(outfp, "} }");
}
#endif

PRIVATE void do_times(pEnv env)
{
    int num;
    Node *prog;

    ONEPARAM("times");
    ONEQUOTE("times");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_times);
    ONEPARAM("times");
    INTEGER("times");
    num = env->stk->u.num;
    POP(env->stk);
    while (num--)
	exeterm(env, prog);
}
#endif
