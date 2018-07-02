/*
    module  : treegenrec.c
    version : 1.8
    date    : 07/02/18
*/

#ifndef NCHECK
int put_treegenrec(void)
{
    Node *prog[3];
    unsigned ident;
    FILE *oldfp, *newfp;

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    prog[1] = stk->next->u.lis;
    prog[0] = stk->next->next->u.lis;
    printstack(outfp);
    fprintf(outfp, "do_cons();");
    fprintf(outfp, "do_cons();");
    fprintf(declfp, "void do_treegenrec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_treegenrec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_treegenrec_%d(void) {", ident);
    fprintf(outfp, "Node *save = stk; POP(stk);");
    fprintf(outfp, "if (stk->op == LIST_) {");
    compile(prog[1]);
    fprintf(outfp, "DUPLICATE(save);");
    fprintf(outfp, "NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(do_treegenrec_%d, 0));", ident);
    fprintf(outfp, "do_cons();");
    compile(prog[2]);
    fprintf(outfp, "} else {");
    compile(prog[0]);
    fprintf(outfp, "} }");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treegenrec  :  T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
static void treegenrec(void)
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
#ifndef NCHECK
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
