/* treerec.c */
PRIVATE void treerecaux()
{
    Node *save;

    if (stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerecaux, 0));
	cons_();
	exeterm(stk->u.lis->u.lis->next);
    } else {
	save = stk;
	POP(stk);
	exeterm(save->u.lis->u.lis);
    }
}

PRIVATE void treerec_()
{
    THREEPARAMS("treerec");
    TWOQUOTES("treerec");
    cons_();
    treerecaux();
}
