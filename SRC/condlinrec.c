/* condlinrec.c */
PRIVATE void condlinrecaux(Node *root)
{
    int num = 0;
    Node *save, *cur;

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
    if (num) {
	exeterm(cur->u.lis->next->u.lis);
	if (cur->u.lis->next->next) {
	    condlinrecaux(root);
	    exeterm(cur->u.lis->next->next->u.lis);
	}
    } else {
	exeterm(cur->u.lis->u.lis);
	if (cur->u.lis->next) {
	    condlinrecaux(root);
	    exeterm(cur->u.lis->next->u.lis);
	}
    }
}

PRIVATE void condlinrec_()
{
    Node *list;

    ONEPARAM("condlinrec");
    LIST("condlinrec");
    CHECKEMPTYLIST(stk->u.lis, "condlinrec");
    list = stk->u.lis;
    POP(stk);
    condlinrecaux(list);
}
