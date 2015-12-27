/* fput.c */
PRIVATE void fput_()
{
    FILE *stm;

    TWOPARAMS("fput");
    if (stk->next->op != FILE_ || (stm = stk->next->u.fil) == 0)
	execerror("file", "fput");
    writefactor(stk, stm);
    fprintf(stm, " ");
    POP(stk);
}
