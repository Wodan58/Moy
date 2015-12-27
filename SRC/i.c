/* i.c */
PRIVATE void i_()
{
    Node *save;

    ONEPARAM("i");
    ONEQUOTE("i");
    save = stk;
    POP(stk);
    exeterm(save->u.lis);
}
