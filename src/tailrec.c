/*
    module  : tailrec.c
    version : 1.18
    date    : 06/20/22
*/
#ifndef TAILREC_C
#define TAILREC_C

/**
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
#ifdef COMPILING
void put_tailrec(pEnv env, Node *prog[3])
{
    static int ident;
    FILE *oldfp;

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
}
#endif

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

    THREEPARAMS("tailrec");
    THREEQUOTES("tailrec");
    prog[2] = env->stk->u.lis;
    POP(env->stk);
    prog[1] = env->stk->u.lis;
    POP(env->stk);
    prog[0] = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_tailrec);
    tailrec(env, prog);
}
#endif
