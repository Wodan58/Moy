/* condnestrec.c */
PRIVATE void condnestrecaux(Node *root)
{
    int num = 0;
    Node *cur, *save;

    cur = root;
    save = stk;

    inside_critical++;
    while (cur && cur->next) {
	stk = save;
	exeterm(cur->u.lis->u.lis);
	if ((num = stk->u.num) != 0)
	    break;
	cur = cur->next;
    }
    if (--inside_critical == 0)
	tmp_release();

    stk = save;
    cur = num ? cur->u.lis->next : cur->u.lis;
    exeterm(cur->u.lis);
    for (cur = cur->next; cur; cur = cur->next) {
	condnestrecaux(root);
	exeterm(cur->u.lis);
    }
}

PRIVATE void condnestrec_()
{
    Node *list;

    ONEPARAM("condnestrec");
    LIST("condnestrec");
    CHECKEMPTYLIST(stk->u.lis, "condnestrec");
    list = stk->u.lis;
    POP(stk);
    condnestrecaux(list);
}
