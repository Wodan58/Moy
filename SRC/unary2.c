/* unary2.c */
PRIVATE void unary2_()
{
    Node *prog, *parm, *save, *result[2];

    THREEPARAMS("unary2");
    ONEQUOTE("unary2");
    prog = stk->u.lis;
    POP(stk);
    parm = stk;
    POP(stk);
    save = stk->next;

    inside_condition++;
    exeterm(prog);
    result[0] = stk;
    stk = save;
    DUPLICATE(parm);
    exeterm(prog);
    result[1] = stk;
    inside_condition--;

    stk = save;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
}
