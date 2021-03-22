/*
    module  : branch.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef BRANCH_C
#define BRANCH_C

#ifndef OLD_RUNTIME
int put_branch(pEnv env)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    printstack(env, outfp);
    fprintf(outfp, "{ /* BRANCH */");
    fprintf(outfp, "int num = env->stk->u.num; POP(env->stk); if (num) {");
    compile(env, prog[0]);
    fprintf(outfp, "} else {");
    compile(env, prog[1]);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
branch  :  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
PRIVATE void do_branch(pEnv env)
{
    int num;
    Node *prog[2];

#ifndef OLD_RUNTIME
    if (compiling && put_branch(env))
	return;
    COMPILE;
#endif
    THREEPARAMS("branch");
    TWOQUOTES("branch");
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    num = env->stk->u.num;
    POP(env->stk);
    exeterm(env, num ? prog[0] : prog[1]);
}
#endif
