/*
    module  : treegenrec.c
    version : 1.12
    date    : 03/28/20
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

#ifndef OLD_RUNTIME
int put_treegenrec(void)
{
    static int ident;
    FILE *oldfp;
    Node *prog[3];

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    prog[1] = stk->next->u.lis;
    prog[0] = stk->next->next->u.lis;
    printstack(outfp);
    fprintf(outfp, "do_cons();");
    fprintf(outfp, "do_cons();");
    fprintf(declfp, "void treegenrec_%d(void);", ++ident);
    fprintf(outfp, "treegenrec_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treegenrec_%d(void) {", ident);
    fprintf(outfp, "Node *save = stk; POP(stk);");
    fprintf(outfp, "if (stk->op == LIST_) {");
    compile(prog[1]);
    fprintf(outfp, "DUPLICATE(save);");
    fprintf(outfp, "NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(treegenrec_%d, 0));", ident);
    fprintf(outfp, "do_cons();");
    compile(prog[2]);
    fprintf(outfp, "} else {");
    compile(prog[0]);
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
void treegenrec(void)
{
    Node *save;

    save = stk;
    POP(stk);
    if (stk->op == LIST_) {
	exeterm(save->u.lis->next->u.lis);
	DUPLICATE(save);
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treegenrec, 0));
	do_cons();
	exeterm(stk->u.lis->u.lis->next->next);
    } else
	exeterm(save->u.lis->u.lis);
}

PRIVATE void do_treegenrec(void)
{
#ifndef OLD_RUNTIME
    if (compiling && put_treegenrec())
	return;
    COMPILE;
#endif
    FOURPARAMS("treegenrec");
    THREEQUOTES("treegenrec");
    do_cons();
    do_cons();
    treegenrec();
}
#endif
