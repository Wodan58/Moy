/*
    module  : cleave.c
    version : 1.16
    date    : 03/15/21
*/
#ifndef CLEAVE_C
#define CLEAVE_C

#ifndef OLD_RUNTIME
int put_cleave(pEnv env)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* CLEAVE */");
    fprintf(outfp, "Node result[2], temp = *env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "result[0] = *env->stk; *env->stk = temp;");
    compile(env, prog[1]);
    fprintf(outfp, "result[1] = *env->stk; *env->stk = result[0];");
    fprintf(outfp, "DUPLICATE(&result[1]); }");
    return 1;
}
#endif

/**
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
PRIVATE void do_cleave(pEnv env)
{
    Node *prog[2], result[2], temp;

#ifndef OLD_RUNTIME
    if (compiling && put_cleave(env))
	return;
    COMPILE;
#endif
    THREEPARAMS("cleave");
    TWOQUOTES("cleave");
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    temp = *env->stk;		// save X
    exeterm(env, prog[0]);
    result[0] = *env->stk;
    *env->stk = temp;		// restore X
    exeterm(env, prog[1]);
    result[1] = *env->stk;
    *env->stk = result[0];		// push results
    DUPLICATE(&result[1]);
}
#endif
