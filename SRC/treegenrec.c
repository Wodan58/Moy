/* treegenrec.c */
PRIVATE void treegenrecaux()
{
    Node *save;

    save = stk;
    POP(stk);
    if (stk->op == LIST_) {
	exeterm(save->u.lis->next->u.lis);
	DUPLICATE(save);
	PUSH(LIST_, ANON_FUNCT_NEWNODE(treegenrecaux, 0));
	cons_();
	exeterm(stk->u.lis->u.lis->next->next);
    } else
	exeterm(save->u.lis->u.lis);
}

PRIVATE void treegenrec_()
{
    FOURPARAMS("treegenrec");
    THREEQUOTES("treegenrec");
    cons_();
    cons_();
    treegenrecaux();
}
