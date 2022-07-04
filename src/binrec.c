/*
    module  : binrec.c
    version : 1.18
    date    : 06/20/22
*/
#ifndef BINREC_C
#define BINREC_C

/**
binrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
#ifdef COMPILING
void put_binrec(pEnv env, Node *prog[4])
{
    static int ident;
    FILE *oldfp;

    fprintf(declfp, "void binrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "binrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void binrec_%d(pEnv env) {", ident);
    fprintf(outfp, "int num; Node *save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save; if (num) {");
    compile(env, prog[1]);
    fprintf(outfp, "} else {");
    compile(env, prog[2]);
    fprintf(outfp, "save = env->stk; POP(env->stk);\n");
    fprintf(outfp, "binrec_%d(env);", ident);
    fprintf(outfp, "DUPLICATE(save);");
    fprintf(outfp, "binrec_%d(env);", ident);
    compile(env, prog[3]);
    fprintf(outfp, "} }\n");
    closefile(outfp);
    outfp = oldfp;
}
#endif

void binrec(pEnv env, Node *prog[])
{
    int num;
    Node *save;

    save = env->stk;
    exeterm(env, prog[0]);
    num = env->stk->u.num;
    env->stk = save;
    if (num)
	exeterm(env, prog[1]);
    else {
	exeterm(env, prog[2]);
	save = env->stk;
	POP(env->stk);
	binrec(env, prog);
	DUPLICATE(save);
	binrec(env, prog);
	exeterm(env, prog[3]);
    }
}

PRIVATE void do_binrec(pEnv env)
{
    Node *prog[4];

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
    INSTANT(put_binrec);
    binrec(env, prog);
}
#endif
