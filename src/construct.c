/*
    module  : construct.c
    version : 1.13
    date    : 05/18/19
*/
#ifndef CONSTRUCT_X
#define CONSTRUCT_C

#ifdef NEW_RUNTIME
void do_construct(void)
{
    code_t *list, *prog, *root = 0, *cur, *last, *save[2];

    TRACE;
    list = (code_t *)do_pop();
    prog = (code_t *)do_pop();
    save[0] = stk2lst();
    execute(prog);
    for (; list; list = list->next) {
	save[1] = stk2lst();
	execute(list->list);
	cur = joy_code();
	cur->num = do_pop();
	if (!root)
	    last = root = cur;
	else
	    last = last->next = cur;
	lst2stk(save[1]);
    }
    lst2stk(save[0]);
    for (cur = root; cur; cur = cur->next)
	do_push(cur->num);
}
#else
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
    if (new_version)
	fprintf(outfp, "code_t *root = 0, *cur, *last, *save[2];");
    else
	fprintf(outfp, "Node *root = 0, *save[2];");
    fprintf(outfp, "save[0] = stk2lst();");
    compile(prog);
    for (; list; list = list->next) {
	fprintf(outfp, "save[1] = stk2lst();");
	compile(list->u.lis);
	if (new_version) {
	    fprintf(outfp, "cur = joy_code(); cur->num = do_pop();");
	    fprintf(outfp, "if (!root) last = root = cur;");
	    fprintf(outfp, "else last = last->next = cur;");
	} else {
	    fprintf(outfp, "root = newnode(stk->op, stk->u.ptr, root);");
	    fprintf(outfp, "stk = 0;");
	}
	fprintf(outfp, "lst2stk(save[1]);");
    }
    if (!new_version)
	fprintf(outfp, "stk = 0;");
    fprintf(outfp, "lst2stk(save[0]);");
    if (!new_version)
	fprintf(outfp, "root = reverse(root);");
    fprintf(outfp, "while (root) {");
    if (new_version)
	fprintf(outfp, "do_push(root->num);");
    else
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
    }
    stk = 0;
    lst2stk(save[0]);
    for (list = reverse(root); list; list = list->next)
	DUPLICATE(list);
}
#endif
#endif
