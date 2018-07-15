/*
    module  : fputchars.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FPUTCHARS_X
#define FPUTCHARS_C

#ifdef NEW_RUNTIME
void do_fputchars(void)
{
    char *str;

    TRACE;
    str = (char *)do_pop();
    fprintf((FILE *)stk[-1], "%s", str);
}
#else
/**
fputchars  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
PRIVATE void do_fputchars(void)
{
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fputchars");
#ifndef NCHECK
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fputchars");
#endif
    str = stk->u.str;
    POP(stk);
    fprintf(stk->u.fil, "%s", str);
}
#endif
#endif
