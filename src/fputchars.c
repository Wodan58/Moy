/*
    module  : fputchars.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

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
