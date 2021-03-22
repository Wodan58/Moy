/*
    module  : tailrec.c
    version : 1.17
    date    : 03/15/21
*/
#ifndef TAILREC_C
#define TAILREC_C

#ifndef OLD_RUNTIME
int put_tailrec(pEnv env)
{
    static int ident;
    FILE *oldfp;
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
    fprintf(declfp, "void tailrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "tailrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void tailrec_%d(pEnv env) {", ident);
    fprintf(outfp, "int num; Node *save; for (;;) {");
    fprintf(outfp, "save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save; if (num) {");
    compile(env, prog[1]);
    fprintf(outfp, "break; }");
    compile(env, prog[2]);
    fprintf(outfp, "} }\n");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void tailrec(pEnv env, Node *prog[])
{
    int num;
    Node *save;

tailrec:
    save = env->stk;
    exeterm(env, prog[0]);
    num = env->stk->u.num;
    env->stk = save;
    if (num)
	exeterm(env, prog[1]);
    else {
	exeterm(env, prog[2]);
	goto tailrec;
    }
}

PRIVATE void do_tailrec(pEnv env)
{
    Node *prog[3];

#ifndef OLD_RUNTIME
    if (compiling && put_tailrec(env))
	return;
    COMPILE;
#endif
    THREEPARAMS("tailrec");
    THREEQUOTES("tailrec");
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    tailrec(env, prog);
}
#endif
