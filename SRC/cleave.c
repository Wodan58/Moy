/* cleave.c */
PRIVATE void cleave_()
{
    Node *prog[2], *result[2], *save;

    THREEPARAMS("cleave");
    TWOQUOTES("cleave");
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    save = stk;

    inside_condition++;
    exeterm(prog[0]);
    result[0] = stk;
    stk = save;
    exeterm(prog[1]);
    result[1] = stk;
    inside_condition--;

    stk = save;
    POP(stk);
    DUPLICATE(result[0]);
    DUPLICATE(result[1]);
}
