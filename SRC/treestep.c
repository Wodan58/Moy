/*
    module  : treestep.c
    version : 1.4
    date    : 04/15/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_treestep(void)
{
    Node *prog;
    unsigned ident;
    FILE *oldfp, *newfp;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "void do_treestep_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_treestep_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_treestep_%d(void) {", ident);
    fprintf(outfp, "Node *cur;");
    fprintf(outfp, "if (stk->op != LIST_) {");
    fprintf(outfp, "DUPLICATE(cur);");
    add_history(INTEGER_);
    evaluate(prog);
    fprintf(outfp, "} else {");
    fprintf(outfp, "cur = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; cur; cur = cur->next) {");
    fprintf(outfp, "do_treestep_%d(); } } }", ident);
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/*
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
static void do_treestepaux(Node *item, Node *prog)
{
    Node *cur;

    if (item->op != LIST_) {
	DUPLICATE(item);
	exeterm(prog);
    } else for (cur = item->u.lis; cur; cur = cur->next)
	do_treestepaux(cur, prog);
}

PRIVATE void do_treestep(void)
{
    Node *item, *prog;

#ifndef NCHECK
    if (optimizing && put_treestep())
	return;
    COMPILE;
    TWOPARAMS("treestep");
    ONEQUOTE("treestep");
#endif
    prog = stk->u.lis;
    POP(stk);
    item = stk;
    POP(stk);
    do_treestepaux(item, prog);
}
