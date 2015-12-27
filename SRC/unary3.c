/* unary3.c */
PRIVATE void unary3_()
{
    Node *prog, *first, *second, *save, *result[3];

    FOURPARAMS("unary3");
    ONEQUOTE("unary3");
    prog = stk->u.lis;
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
    inside_condition--;

    stk = save;
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
    DUPLICATE(result[2]);
}
