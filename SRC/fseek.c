/* fseek.c */
PRIVATE void fseek_()
{
    long_t pos;
    int whence;

    THREEPARAMS("fseek");
    INTEGER("fseek");
    INTEGER2("fseek");
    whence = stk->u.num;
    POP(stk);
    pos = stk->u.num;
    POP(stk);
    FILE("fseek");
    PUSH(BOOLEAN_, fseek(stk->u.fil, pos, whence) != 0);
}
