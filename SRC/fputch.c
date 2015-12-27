/* fputch.c */
PRIVATE void fputch_()
{
    int ch;

    TWOPARAMS("fputch");
    INTEGER("fputch");
    ch = stk->u.num;
    POP(stk);
    FILE("fputch");
    putc(ch, stk->u.fil);
}
