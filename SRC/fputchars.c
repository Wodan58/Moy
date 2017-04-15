/*
    module  : fputchars.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
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
