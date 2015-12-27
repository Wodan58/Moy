/* fget.c */
PRIVATE void fget_()
{
    FILE *stm = 0;

    ONEPARAM("fget");
    if (stk->op != FILE_ || (stm = stk->u.fil) == 0)
	execerror("file", "fget");
    redirect(stm);
    getsym();
    readfactor();
}
