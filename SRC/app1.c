/* app1.c */
PRIVATE void app1_()
{
    Node *prog;

    TWOPARAMS("app1");
    ONEQUOTE("app1");
    prog = stk->u.lis;
    POP(stk);
    exeterm(prog);
}
