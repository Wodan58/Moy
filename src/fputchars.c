/*
    module  : fputchars.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef FPUTCHARS_X
#define FPUTCHARS_C

/**
fputchars  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
PRIVATE void do_fputchars(void)
{
    char *str;

#ifndef NCHECK
    COMPILE;
#endif
    TWOPARAMS("fputchars");
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fputchars");
    str = stk->u.str;
    POP(stk);
    fprintf(stk->u.fil, "%s", str);
}

/**
fputstring  :  S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/




/* fputchars.c */
#endif
