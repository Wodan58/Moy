/*
    module  : branch.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef BRANCH_C
#define BRANCH_C

/**
branch  :  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
#ifdef COMPILING
void put_branch(pEnv env, Node *prog[2])
{
    fprintf(outfp, "{ /* BRANCH */");
    fprintf(outfp, "int num = env->stk->u.num; POP(env->stk); if (num) {");
    compile(env, prog[0]);
    fprintf(outfp, "} else {");
    compile(env, prog[1]);
    fprintf(outfp, "} }");
}
#endif

PRIVATE void do_branch(pEnv env)
{
    int num;
    Node *prog[2];

    TWOPARAMS("branch");
    TWOQUOTES("branch");
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_branch);
    ONEPARAM("branch");
    num = env->stk->u.num;
    POP(env->stk);
    exeterm(env, num ? prog[0] : prog[1]);
}
#endif
