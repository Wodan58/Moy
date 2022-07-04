/*
    module  : treerec.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef TREEREC_C
#define TREEREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

/**
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
#ifdef COMPILING
void put_treerec(pEnv env, Node *prog)
{
    static int ident;
    FILE *oldfp;

    fprintf(outfp, "do_cons(env);");
    fprintf(declfp, "void treerec_%d(pEnv env);", ++ident);
    fprintf(outfp, "treerec_%d(env);", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treerec_%d(pEnv env) {", ident);
    fprintf(outfp, "if (env->stk->next->op == LIST_) { NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(treerec_%d, 0));", ident);
    fprintf(outfp, "do_cons(env);");
    compile(env, prog->u.lis->u.lis->next);
    fprintf(outfp, "} else { POP(env->stk);");
    compile(env, prog->u.lis->u.lis);
    fprintf(outfp, "} }");
    closefile(outfp);
    outfp = oldfp;
}
#endif

void treerec(pEnv env)
{
    Node *prog;

    if (env->stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerec, 0));
	do_cons(env);
	exeterm(env, env->stk->u.lis->u.lis->next);
    } else {
	prog = env->stk;
	POP(env->stk);
	exeterm(env, prog->u.lis->u.lis);
    }
}

PRIVATE void do_treerec(pEnv env)
{
    Node *prog;

    TWOPARAMS("treerec");
    TWOQUOTES("treerec");
    do_cons(env);
    prog = env->stk;
    POP(env->stk);
    INSTANT(put_treerec);
    ONEPARAM("treerec");
    DUPLICATE(prog); 
    treerec(env);
}
#endif
