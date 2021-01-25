/*
    module  : construct.c
    version : 1.15
    date    : 01/24/21
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

#ifndef OLD_RUNTIME
int put_construct(void)
{
    Node *list, *prog;

    if (!(LIST_1 && LIST_2))
	return 0;
    list = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* CONSTRUCT */");
    fprintf(outfp, "Node *root = 0, *save[2];");
    fprintf(outfp, "save[0] = stk2lst();");
    compile(prog);
    for (; list; list = list->next) {
	fprintf(outfp, "save[1] = stk2lst();");
	compile(list->u.lis);
	fprintf(outfp, "root = newnode(stk->op, stk->u.ptr, root);");
	fprintf(outfp, "stk = 0;");
	fprintf(outfp, "lst2stk(save[1]);");
	fprintf(outfp, "if (!stk) break;");
    }
    fprintf(outfp, "stk = 0;");
    fprintf(outfp, "lst2stk(save[0]);");
    fprintf(outfp, "root = reverse(root);");
    fprintf(outfp, "while (root) {");
    fprintf(outfp, "DUPLICATE(root);");
    fprintf(outfp, "root = root->next; } }");
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
    Node *list, *prog, *root = 0, *save[2];

#ifndef OLD_RUNTIME
    if (compiling && put_construct())
	return;
    COMPILE;
#endif
    TWOPARAMS("construct");
    TWOQUOTES("construct");
    list = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    save[0] = stk2lst();
    exeterm(prog);
    for (; list; list = list->next) {
	save[1] = stk2lst();
	exeterm(list->u.lis);
	root = newnode(stk->op, stk->u.ptr, root);
	stk = 0;
	lst2stk(save[1]);
	if (!stk)
	    break;
    }
    stk = 0;
    lst2stk(save[0]);
    for (list = reverse(root); list; list = list->next)
	DUPLICATE(list);
}
#endif
