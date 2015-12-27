/* fputchars.c */
PRIVATE void fputchars_()
{
    FILE *stm;

    TWOPARAMS("fputchars");
    if (stk->next->op != FILE_ || (stm = stk->next->u.fil) == 0)
	execerror("file", "fputchars");
    fprintf(stm, "%s", stk->u.str);
    POP(stk);
}
