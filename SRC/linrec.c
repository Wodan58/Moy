/* linrec.c */
PRIVATE void linrecaux(Node *first, Node *second, Node *third, Node *fourth)
{
    int num;
    Node *save;

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
	linrecaux(first, second, third, fourth);
	exeterm(fourth);
    }
}

PRIVATE void linrec_()
{
    Node *first, *second, *third, *fourth;

    FOURPARAMS("linrec");
    FOURQUOTES("linrec");
    fourth = stk->u.lis;
    POP(stk);
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    linrecaux(first, second, third, fourth);
}
