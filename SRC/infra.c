/* infra.c */
PRIVATE void infra_()
{
    Node *prog, *save;

    TWOPARAMS("infra");
    ONEQUOTE("infra");
    LIST2("infra");
    prog = stk->u.lis;
    POP(stk);
    save = stk->next;
    stk = stk->u.lis;

    inside_condition++;
    exeterm(prog);
    inside_condition--;

    prog = stk;
    stk = save;
    PUSH(LIST_, prog);
}
