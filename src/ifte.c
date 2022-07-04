/*
    module  : ifte.c
    version : 1.20
    date    : 06/20/22
*/
#ifndef IFTE_C
#define IFTE_C

/**
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
#ifdef COMPILING
void put_ifte(pEnv env, Node *prog[3])
{
    fprintf(outfp, "{ /* IFTE */");
    fprintf(outfp, "int num; Node *save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save; if (num) {");
    compile(env, prog[1]);
    fprintf(outfp, "} else {");
    compile(env, prog[2]);
    fprintf(outfp, "} }");
}
#endif

PRIVATE void do_ifte(pEnv env)
{
    Node *prog[3], *save;

    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_ifte);
    save = env->stk;
    exeterm(env, prog[0]);
    prog[0] = env->stk->u.num ? prog[1] : prog[2];
    env->stk = save;
    exeterm(env, prog[0]);
}
#endif
