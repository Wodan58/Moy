/*
    module  : binrec.c
    version : 1.17
    date    : 03/15/21
*/
#ifndef BINREC_C
#define BINREC_C

#ifndef OLD_RUNTIME
int put_binrec(pEnv env)
{
    static int ident;
    FILE *oldfp;
    Node *prog[4];

    if (!(LIST_1 && LIST_2 && LIST_3 && LIST_4))
	return 0;
    prog[3] = env->stk->u.lis;
    POP(env->stk);
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(declfp, "void binrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "binrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void binrec_%d(pEnv env) {", ident);
    fprintf(outfp, "int num; Node *save, temp; save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save; if (num) {");
    compile(env, prog[1]);
    fprintf(outfp, "} else {");
    compile(env, prog[2]);
    fprintf(outfp, "temp = *env->stk; POP(env->stk);\n");
    fprintf(outfp, "binrec_%d(env);", ident);
    fprintf(outfp, "DUPLICATE(&temp);");
    fprintf(outfp, "binrec_%d(env);", ident);
    compile(env, prog[3]);
    fprintf(outfp, "} }\n");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
binrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
void binrec(pEnv env, Node *prog[])
{
    int num;
    Node *save, temp;

    save = env->stk;
    exeterm(env, prog[0]);
    num = env->stk->u.num;
    env->stk = save;
    if (num)
	exeterm(env, prog[1]);
    else {
	exeterm(env, prog[2]);
	temp = *env->stk;
	POP(env->stk);
	binrec(env, prog);
	DUPLICATE(&temp);
	binrec(env, prog);
	exeterm(env, prog[3]);
    }
}

PRIVATE void do_binrec(pEnv env)
{
    Node *prog[4];

#ifndef OLD_RUNTIME
    if (compiling && put_binrec(env))
	return;
    COMPILE;
#endif
    FOURPARAMS("binrec");
    FOURQUOTES("binrec");
    prog[3] = env->stk->u.lis;
    POP(env->stk);
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    binrec(env, prog);
}
#endif
