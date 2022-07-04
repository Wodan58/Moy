/*
    module  : linrec.c
    version : 1.18
    date    : 06/20/22
*/
#ifndef LINREC_C
#define LINREC_C

/**
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
#ifdef COMPILING
void put_linrec(pEnv env, Node *prog[4])
{
    static int ident;
    FILE *oldfp;

    fprintf(declfp, "void linrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "linrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void linrec_%d(pEnv env) {", ident);
    fprintf(outfp, "int num; Node *save; save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save; if (num) {");
    compile(env, prog[1]);
    fprintf(outfp, "} else {");
    compile(env, prog[2]);
    fprintf(outfp, "linrec_%d(env);", ident);
    compile(env, prog[3]);
    fprintf(outfp, "} }\n");
    closefile(outfp);
    outfp = oldfp;
}
#endif

void linrec(pEnv env, Node *prog[])
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
	linrec(env, prog);
	exeterm(env, prog[3]);
    }
}

PRIVATE void do_linrec(pEnv env)
{
    Node *prog[4];

    FOURPARAMS("linrec");
    FOURQUOTES("linrec");
    prog[3] = env->stk->u.lis;
    POP(env->stk);
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_linrec);
    linrec(env, prog);
}
#endif
