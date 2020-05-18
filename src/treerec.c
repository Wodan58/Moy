/*
    module  : treerec.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef TREEREC_C
#define TREEREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

#ifndef OLD_RUNTIME
int put_treerec(void)
{
    static int ident;
    FILE *oldfp;
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    prog[0] = stk->next->u.lis;
    printstack(outfp);
    fprintf(outfp, "do_cons();");
    fprintf(declfp, "void treerec_%d(void);", ++ident);
    fprintf(outfp, "treerec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treerec_%d(void) {", ident);
    fprintf(outfp, "if (stk->next->op == LIST_) { NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(treerec_%d, 0));", ident);
    fprintf(outfp, "do_cons();");
    compile(prog[1]);
    fprintf(outfp, "} else { POP(stk);");
    compile(prog[0]);
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
void treerec(void)
{
    Node *save;

    if (stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerec, 0));
	do_cons();
	exeterm(stk->u.lis->u.lis->next);
    } else {
	save = stk;
	POP(stk);
	exeterm(save->u.lis->u.lis);
    }
}

PRIVATE void do_treerec(void)
{
#ifndef OLD_RUNTIME
    if (compiling && put_treerec())
	return;
    COMPILE;
#endif
    THREEPARAMS("treerec");
    TWOQUOTES("treerec");
    do_cons();
    treerec();
}
#endif
