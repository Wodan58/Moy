/* ifte.c */
PRIVATE void ifte_()
{
    int num;
    Node *second, *first, *test, *save;

    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    test = stk->u.lis;
    POP(stk);
    save = stk;

    inside_critical++;
    exeterm(test);
    num = stk->u.num;
    if (--inside_critical == 0)
	tmp_release();

    stk = save;
    exeterm(num ? first : second);
}
