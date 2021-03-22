/*
    module  : treerec.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef TREEREC_C
#define TREEREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

#ifndef OLD_RUNTIME
int put_treerec(pEnv env)
{
    static int ident;
    FILE *oldfp;
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = env->stk->u.lis;
    prog[0] = env->stk->next->u.lis;
    printstack(env, outfp);
    fprintf(outfp, "do_cons(env);");
    fprintf(declfp, "void treerec_%d(pEnv env);", ++ident);
    fprintf(outfp, "treerec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treerec_%d(pEnv env) {", ident);
    fprintf(outfp, "if (env->stk->next->op == LIST_) { NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(treerec_%d, 0));", ident);
    fprintf(outfp, "do_cons(env);");
    compile(env, prog[1]);
    fprintf(outfp, "} else { POP(env->stk);");
    compile(env, prog[0]);
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec(pEnv env)
{
    Node *save;

    if (env->stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerec, 0));
	do_cons(env);
	exeterm(env, env->stk->u.lis->u.lis->next);
    } else {
	save = env->stk;
	POP(env->stk);
	exeterm(env, save->u.lis->u.lis);
    }
}

PRIVATE void do_treerec(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && put_treerec(env))
	return;
    COMPILE;
#endif
    THREEPARAMS("treerec");
    TWOQUOTES("treerec");
    do_cons(env);
    treerec(env);
}
#endif
