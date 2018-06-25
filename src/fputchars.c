/*
    module  : fputchars.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
fputchars  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
PRIVATE void do_fputchars(void)
{
    char *str;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    TWOPARAMS("fputchars");
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fputchars");
#endif
    str = stk->u.str;
    POP(stk);
    fprintf(stk->u.fil, "%s", str);
}

/**
fputstring  :  S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/




/* fputchars.c */
