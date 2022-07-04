/*
    module  : cleave.c
    version : 1.17
    date    : 06/20/22
*/
#ifndef CLEAVE_C
#define CLEAVE_C

/**
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
#ifdef COMPILING
void put_cleave(pEnv env, Node *prog[2])
{
    fprintf(outfp, "{ /* CLEAVE */");
    fprintf(outfp, "Node *result[2], *save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "result[0] = env->stk; env->stk = save;");
    compile(env, prog[1]);
    fprintf(outfp, "result[1] = env->stk; env->stk = save->next;");
    fprintf(outfp, "DUPLICATE(result[0]);");
    fprintf(outfp, "DUPLICATE(result[1]); }");
}
#endif

PRIVATE void do_cleave(pEnv env)
{
    Node *prog[2], *result[2], *save;

    TWOPARAMS("cleave");
    TWOQUOTES("cleave");
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_cleave);
    save = env->stk;		// save X
    exeterm(env, prog[0]);
    result[0] = env->stk;
    env->stk = save;		// restore X
    exeterm(env, prog[1]);
    result[1] = env->stk;
    env->stk = save->next;
    DUPLICATE(result[0]);	// push results
    DUPLICATE(result[1]);
}
#endif
