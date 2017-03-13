/*
    module  : treerec.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_treerec(void)
{
    Node *prog[2];
    unsigned ident;
    FILE *oldfp, *newfp;

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    prog[0] = stk->next->u.lis;
    printstack(outfp);
    fprintf(outfp, "do_cons();");
    fprintf(outfp, "void do_treerec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_treerec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_treerec_%d(void) {", ident);
    fprintf(outfp, "if (stk->next->op == LIST_) {");
    fprintf(outfp, "NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(do_treerec_%d, 0));", ident);
    fprintf(outfp, "do_cons();");
    evaluate(prog[1]);
    fprintf(outfp, "} else { POP(stk);");
    evaluate(prog[0]);
    fprintf(outfp, "} }");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/*
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
static void do_treerecaux(void)
{
    Node *save;

    if (stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(do_treerecaux, 0));
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
#ifndef NCHECK
    if (optimizing && put_treerec())
	return;
    COMPILE;
    THREEPARAMS("treerec");
    TWOQUOTES("treerec");
#endif
    do_cons();
    do_treerecaux();
}
