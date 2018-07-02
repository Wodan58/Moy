/*
    module  : construct.c
    version : 1.10
    date    : 07/02/18
*/

#ifndef NCHECK
int put_construct(void)
{
    Node *cur, *prog;

    if (!(LIST_1 && LIST_2))
	return 0;
    cur = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* CONSTRUCT */");
    fprintf(outfp, "Node *save[2], *root = 0;");
    fprintf(outfp, "save[0] = stk;");
    compile(prog);
    for (; cur; cur = cur->next) {
	fprintf(outfp, "CONDITION; save[1] = stk;");
	compile(cur->u.lis);
	fprintf(outfp, "root = heapnode(stk->op, stk->u.ptr, root);");
	fprintf(outfp, "stk = save[1]; RELEASE;");
    }
    fprintf(outfp, "stk = save[0]; while (root) {");
    fprintf(outfp, "DUPLICATE(root); root = root->next; } }");
    return 1;
}
#endif

/**
construct  :  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
PRIVATE void do_construct(void)
{
    Node *cur, *prog, *root = 0, *save[2];

#ifndef NCHECK
    if (compiling && put_construct())
	return;
    COMPILE;
#endif
    TWOPARAMS("construct");
    TWOQUOTES("construct");
    cur = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    save[0] = stk;
    exeterm(prog);
    for (; cur; cur = cur->next) {
	CONDITION;
	save[1] = stk;
	exeterm(cur->u.lis);
	root = heapnode(stk->op, stk->u.ptr, root);
	stk = save[1];
	RELEASE;
    }
    stk = save[0];
    for (cur = root; cur; cur = cur->next)
	DUPLICATE(cur);
}
