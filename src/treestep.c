/*
    module  : treestep.c
    version : 1.10
    date    : 07/15/18
*/
#ifndef TREESTEP_X
#define TREESTEP_C

#ifdef NEW_RUNTIME
void treestep(code_t *item, code_t *prog)
{
    TRACE;
    if (!IS_LIST(item)) {
	do_push((node_t)item);
	execute(prog);
    } else for (; item; item = item->next)
	treestep(item->list, prog);
}

void do_treestep(void)
{
    code_t *prog, *item;

    prog = (code_t *)do_pop();
    item = (code_t *)do_pop();
    treestep(item, prog);
}
#else
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
    if (new_version) {
	fprintf(outfp, "void treestep_%d(code_t *item);", ++ident);
	fprintf(outfp, "treestep_%d((code_t *)do_pop());", ident);
    } else {
	fprintf(outfp, "void treestep_%d(Node *item);", ++ident);
	fprintf(outfp, "{ Node *item = stk; POP(stk);");
	fprintf(outfp, "treestep_%d(item); }", ident);
    }
    oldfp = outfp;
    outfp = nextfile();
    if (new_version)
	fprintf(outfp, "void treestep_%d(code_t *item) { TRACE;", ident);
    else
	fprintf(outfp, "void treestep_%d(Node *item) {", ident);
    if (new_version)
	fprintf(outfp, "if (!IS_LIST(item)) { do_push((node_t)item);");
    else
	fprintf(outfp, "if (item->op != LIST_) { DUPLICATE(item);");
    compile(prog);
    fprintf(outfp, "} else ");
    if (new_version) {
	fprintf(outfp, "for (; item; item = item->next)");
	fprintf(outfp, "treestep_%d(item->list); }", ident);
    } else {
	fprintf(outfp, "for (item = item->u.lis; item; item = item->next)");
	fprintf(outfp, "treestep_%d(item); }", ident);
    }
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
#endif
