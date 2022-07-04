/*
    module  : treegenrec.c
    version : 1.14
    date    : 06/20/22
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

/**
treegenrec  :  T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
#ifdef COMPILING
void put_treegenrec(pEnv env, Node *prog)
{
    static int ident;
    FILE *oldfp;

    fprintf(declfp, "void treegenrec_%d(pEnv env);", ++ident);
    fprintf(outfp, "treegenrec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treegenrec_%d(pEnv env) {", ident);
    fprintf(outfp, "Node *save = env->stk; POP(env->stk);");
    fprintf(outfp, "if (env->stk->op == LIST_) {");
    compile(env, prog->u.lis->next->u.lis);	/* O2 */
    fprintf(outfp, "DUPLICATE(save);");
    fprintf(outfp, "NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(treegenrec_%d, 0));", ident);
    fprintf(outfp, "do_cons(env);");
    compile(env, prog->u.lis->next->next);	/* C */
    fprintf(outfp, "} else {");
    compile(env, prog->u.lis->u.lis);		/* O1 */
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
}
#endif

void treegenrec(pEnv env)
{
    Node *prog;

    prog = env->stk;	/* prog = [[O1] [O2] C] */
    POP(env->stk);	/* prog->u.lis = [O1] [O2] C */
    if (env->stk->op == LIST_) {
	exeterm(env, prog->u.lis->next->u.lis);	/* O2 */
	DUPLICATE(prog);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treegenrec, 0));
	do_cons(env);
	exeterm(env, prog->u.lis->next->next);	/* C */
    } else
	exeterm(env, prog->u.lis->u.lis);	/* O1 */
}

PRIVATE void do_treegenrec(pEnv env)
{
    Node *prog;

    THREEPARAMS("treegenrec");
    THREEQUOTES("treegenrec");
    do_cons(env);
    do_cons(env);
    prog = env->stk;
    POP(env->stk);
    INSTANT(put_treegenrec);
    ONEPARAM("treegenrec");
    DUPLICATE(prog); 
    treegenrec(env);
}
#endif
