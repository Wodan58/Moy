/*
    module  : genrec.c
    version : 1.18
    date    : 03/15/21
*/
#ifndef GENREC_C
#define GENREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

#ifndef OLD_RUNTIME
int put_genrec(pEnv env)
{
    static int ident;
    FILE *oldfp;
    Node *prog[4];

    if (!(LIST_1 && LIST_2 && LIST_3 && LIST_4))
	return 0;
    prog[3] = env->stk->u.lis;
    prog[2] = env->stk->next->u.lis;
    prog[1] = env->stk->next->next->u.lis;
    prog[0] = env->stk->next->next->next->u.lis;
    printstack(env, outfp);
    fprintf(outfp, "do_cons(env);");
    fprintf(outfp, "do_cons(env);");
    fprintf(outfp, "do_cons(env);");
    fprintf(declfp, "void genrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "genrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void genrec_%d(pEnv env) {", ident);
    fprintf(outfp, "int num; Node *code, *save;");
    fprintf(outfp, "code = env->stk->u.lis; POP(env->stk);");
    fprintf(outfp, "save = env->stk;");
    compile(env, prog[0]);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
    fprintf(outfp, "if (num) {");
    compile(env, prog[1]);
    fprintf(outfp, "} else {");
    compile(env, prog[2]);
    fprintf(outfp, "PUSH_PTR(LIST_, code); NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(genrec_%d, 0));", ident);
    fprintf(outfp, "do_cons(env);");
    compile(env, prog[3]);
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
genrec  :  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void genrec(pEnv env)
{
    int num;
    Node *code, *save;

    code = env->stk->u.lis;
    POP(env->stk);
    save = env->stk;
    exeterm(env, code->u.lis);
    num = env->stk->u.num;
    env->stk = save;
    if (num)
	exeterm(env, code->next->u.lis);
    else {
	exeterm(env, code->next->next->u.lis);
	PUSH_PTR(LIST_, code);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(genrec, 0));
	do_cons(env);
	exeterm(env, code->next->next->next);
    }
}

PRIVATE void do_genrec(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && put_genrec(env))
	return;
    COMPILE;
#endif
    FOURPARAMS("genrec");
    FOURQUOTES("genrec");
    do_cons(env);
    do_cons(env);
    do_cons(env);
    genrec(env);
}
#endif
