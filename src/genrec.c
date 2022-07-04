/*
    module  : genrec.c
    version : 1.19
    date    : 06/20/22
*/
#ifndef GENREC_C
#define GENREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

/**
genrec  :  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
#ifdef COMPILING
void put_genrec(pEnv env, Node *prog)
{
    static int ident;
    FILE *oldfp;

    PUSH_PTR(LIST_, prog);
    fprintf(declfp, "void genrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "genrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void genrec_%d(pEnv env) {", ident);
    fprintf(outfp, "int num; Node *prog, *save;");
    fprintf(outfp, "prog = env->stk->u.lis; POP(env->stk); save = env->stk;");
    compile(env, prog->u.lis);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save; if (num) {");
    compile(env, prog->next->u.lis);
    fprintf(outfp, "} else {");
    compile(env, prog->next->next->u.lis);
    fprintf(outfp, "PUSH_PTR(LIST_, prog);");
    fprintf(outfp, "PUSH_PTR(LIST_, ANON_FUNCT_NEWNODE(genrec_%d, 0));", ident);
    fprintf(outfp, "do_cons(env);");
    compile(env, prog->next->next->next);
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
}
#endif

void genrec(pEnv env)
{
    int num;
    Node *prog, *save;

    prog = env->stk->u.lis;
    POP(env->stk);
    save = env->stk;
    exeterm(env, prog->u.lis);
    num = env->stk->u.num;
    env->stk = save;
    if (num)
	exeterm(env, prog->next->u.lis);
    else {
	exeterm(env, prog->next->next->u.lis);
	PUSH_PTR(LIST_, prog);
	PUSH_PTR(LIST_, ANON_FUNCT_NEWNODE(genrec, 0));
	do_cons(env);
	exeterm(env, prog->next->next->next);
    }
}

PRIVATE void do_genrec(pEnv env)
{
    Node *prog;

    FOURPARAMS("genrec");
    FOURQUOTES("genrec");
    do_cons(env);
    do_cons(env);
    do_cons(env);
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_genrec);
    PUSH_PTR(LIST_, prog);
    genrec(env);
}
#endif
