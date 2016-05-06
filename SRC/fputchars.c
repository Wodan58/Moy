/*
    module  : fputchars.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fputchars  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
/* fputchars.c */
PRIVATE void fputchars_(void)
{
    FILE *stm;

    TWOPARAMS("fputchars");
#ifdef RUNTIME_CHECKS
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fputchars");
#endif
    stm = stk->next->u.fil;
    fprintf(stm, "%s", stk->u.str);
    POP(stk);
}
