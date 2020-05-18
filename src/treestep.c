/*
    module  : treestep.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef TREESTEP_C
#define TREESTEP_C

#ifndef OLD_RUNTIME
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
    fprintf(outfp, "void treestep_%d(Node *item);", ++ident);
    fprintf(outfp, "{ Node *item = stk; POP(stk);");
    fprintf(outfp, "treestep_%d(item); }", ident);
    oldfp = outfp;
    outfp = nextfile();
    fprintf(outfp, "void treestep_%d(Node *item) {", ident);
    fprintf(outfp, "if (item->op != LIST_) { DUPLICATE(item);");
    compile(prog);
    fprintf(outfp, "} else ");
    fprintf(outfp, "for (item = item->u.lis; item; item = item->next)");
    fprintf(outfp, "treestep_%d(item); }", ident);
    closefile(outfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void treestep(Node *item, Node *prog)
{
    if (item->op != LIST_) {
	DUPLICATE(item);
	exeterm(prog);
    } else for (item = item->u.lis; item; item = item->next)
	treestep(item, prog);
}

PRIVATE void do_treestep(void)
{
    Node *item, *prog;

#ifndef OLD_RUNTIME
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
#endif
