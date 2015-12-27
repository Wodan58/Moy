/* fflush.c */
PRIVATE void fflush_()
{
    ONEPARAM("fflush");
    FILE("fflush");
    fflush(stk->u.fil);
}
