/* times.c */
PRIVATE void times_()
{
    int i, n;
    Node *prog;

    TWOPARAMS("times");
    ONEQUOTE("times");
    INTEGER2("times");
    prog = stk->u.lis;
    POP(stk);
    n = stk->u.num;
    POP(stk);
    for (i = 0; i < n; i++)
	exeterm(prog);
}
