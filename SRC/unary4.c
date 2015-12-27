/* unary4.c */
PRIVATE void unary4_()
{
    Node *prog, *first, *second, *third, *save, *result[4];

    FIVEPARAMS("unary4");
    ONEQUOTE("unary4");
    prog = stk->u.lis;
    POP(stk);
    third = stk;
    POP(stk);
    second = stk;
    POP(stk);
    first = stk;
    POP(stk);
    save = stk->next;

    inside_condition++;
    exeterm(prog);
    result[0] = stk;
    stk = save;
    DUPLICATE(first);
    exeterm(prog);
    result[1] = stk;
    stk = save;
    DUPLICATE(second);
    exeterm(prog);
    result[2] = stk;
    stk = save;
    DUPLICATE(third);
    exeterm(prog);
    result[3] = stk;
    inside_condition--;

    stk = save;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
    DUPLICATE(result[2]);
    DUPLICATE(result[3]);
}
