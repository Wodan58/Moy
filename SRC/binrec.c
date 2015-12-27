/* binrec.c */
PRIVATE void binrecaux(Node *first, Node *second, Node *third, Node *fourth)
{
    int num;
    Node *save, node;

    save = stk;

    inside_critical++;
    exeterm(first);
    num = stk->u.num;
    if (--inside_critical == 0)
	tmp_release();

    stk = save;
    if (num)
	exeterm(second);
    else {
	exeterm(third);
	node = *stk;
	POP(stk);
	binrecaux(first, second, third, fourth);
	DUPLICATE(&node);
	binrecaux(first, second, third, fourth);
	exeterm(fourth);
    }
}

PRIVATE void binrec_()
{
    Node *first, *second, *third, *fourth;

    FOURPARAMS("binrec");
    FOURQUOTES("binrec");
    fourth = stk->u.lis;
    POP(stk);
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    binrecaux(first, second, third, fourth);
}
