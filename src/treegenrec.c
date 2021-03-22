/*
    module  : treegenrec.c
    version : 1.13
    date    : 03/15/21
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

#ifndef OLD_RUNTIME
int put_treegenrec(pEnv env)
{
    static int ident;
    FILE *oldfp;
    Node *prog[3];

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = env->stk->u.lis;
    prog[1] = env->stk->next->u.lis;
    prog[0] = env->stk->next->next->u.lis;
    printstack(env, outfp);
    fprintf(outfp, "do_cons(env);");
    fprintf(outfp, "do_cons(env);");
    fprintf(declfp, "void treegenrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "treegenrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treegenrec_%d(pEnv env) {", ident);
    fprintf(outfp, "Node *save = env->stk; POP(env->stk);");
    fprintf(outfp, "if (env->stk->op == LIST_) {");
    compile(env, prog[1]);
    fprintf(outfp, "DUPLICATE(save);");
    fprintf(outfp, "NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(treegenrec_%d, 0));", ident);
    fprintf(outfp, "do_cons(env);");
    compile(env, prog[2]);
    fprintf(outfp, "} else {");
    compile(env, prog[0]);
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treegenrec  :  T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void treegenrec(pEnv env)
{
    Node *save;

    save = env->stk;
    POP(env->stk);
    if (env->stk->op == LIST_) {
	exeterm(env, save->u.lis->next->u.lis);
	DUPLICATE(save);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treegenrec, 0));
	do_cons(env);
	exeterm(env, env->stk->u.lis->u.lis->next->next);
    } else
	exeterm(env, save->u.lis->u.lis);
}

PRIVATE void do_treegenrec(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && put_treegenrec(env))
	return;
    COMPILE;
#endif
    FOURPARAMS("treegenrec");
    THREEQUOTES("treegenrec");
    do_cons(env);
    do_cons(env);
    treegenrec(env);
}
#endif
