/*
    module  : fputchars.c
    version : 1.6
    date    : 07/02/18
*/

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
