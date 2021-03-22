/*
    module  : ifte.c
    version : 1.19
    date    : 03/15/21
*/
#ifndef IFTE_C
#define IFTE_C

#ifndef OLD_RUNTIME
int put_ifte(pEnv env)
{
    Node *prog[3];

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* IFTE */");
    fprintf(outfp, "int num;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; POP(env->stk); if (num) {");
    compile(env, prog[1]);
    fprintf(outfp, "} else {");
    compile(env, prog[2]);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
PRIVATE void do_ifte(pEnv env)
{
    Node *prog[3] /* , *save */;

#ifndef OLD_RUNTIME
    if (compiling && put_ifte(env))
	return;
    COMPILE;
#endif
    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    exeterm(env, prog[0]);
    prog[0] = env->stk->u.num ? prog[1] : prog[2];
    POP(env->stk);
    exeterm(env, prog[0]);
}
#endif
