/*
    module  : treestep.c
    version : 1.8
    date    : 07/05/18
*/

#ifndef NCHECK
int put_treestep(void)
{
    static int ident;
    Node *prog;
    FILE *oldfp;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(declfp, "void do_treestep_%d(void);", ++ident);
    fprintf(outfp, "do_treestep_%d();", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void do_treestep_%d(void) {", ident);
    fprintf(outfp, "Node *cur;");
    fprintf(outfp, "if (stk->op != LIST_) {");
    fprintf(outfp, "DUPLICATE(cur);");
    compile(prog);
    fprintf(outfp, "} else {");
    fprintf(outfp, "cur = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; cur; cur = cur->next) {");
    fprintf(outfp, "do_treestep_%d(); } } }", ident);
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
static void treestep(Node *item, Node *prog)
{
    Node *cur;

    if (item->op != LIST_) {
	DUPLICATE(item);
	exeterm(prog);
    } else for (cur = item->u.lis; cur; cur = cur->next)
	treestep(cur, prog);
}

PRIVATE void do_treestep(void)
{
    Node *item, *prog;

#ifndef NCHECK
    if (compiling && put_treestep())
	return;
    COMPILE;
#endif
    TWOPARAMS("treestep");
    ONEQUOTE("treestep");
    prog = stk->u.lis;
    POP(stk);
    item = stk;
    POP(stk);
    treestep(item, prog);
}
