/* branch.c */
PRIVATE void branch_()
{
    int num;
    Node *first, *second;

    THREEPARAMS("branch");
    TWOQUOTES("branch");
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    num = stk->u.num;
    POP(stk);
    exeterm(num ? first : second);
}
