/* dip.c */
PRIVATE void dip_()
{
    Node *prog, save;

    TWOPARAMS("dip");
    ONEQUOTE("dip");
    prog = stk->u.lis;
    POP(stk);
    save = *stk;
    POP(stk);
    exeterm(prog);
    DUPLICATE(&save);
}
