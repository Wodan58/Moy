/* construct.c */
PRIVATE void construct_()
{
    Node *cur, *test, *root, *save;

    TWOPARAMS("construct");
    TWOQUOTES("construct");
    cur = stk->u.lis;
    POP(stk);
    test = stk->u.lis;
    POP(stk);
    root = stk;

    inside_condition++;
    exeterm(test);
    for (save = stk; cur; cur = cur->next) {
	stk = save;
	exeterm(cur->u.lis);
	root = newnode(stk->op, stk->u, root);
    }
    inside_condition--;

    stk = root;
}
