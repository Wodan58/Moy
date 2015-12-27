/* tailrec.c */
PRIVATE void tailrecaux(Node *first, Node *second, Node *third)
{
   int num;
   Node *save;

tailrec:
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
	goto tailrec;
    }
}

PRIVATE void tailrec_()
{
    Node *first, *second, *third;

    THREEPARAMS("tailrec");
    THREEQUOTES("tailrec");
    third = stk->u.lis;
    POP(stk);
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    tailrecaux(first, second, third);
}
