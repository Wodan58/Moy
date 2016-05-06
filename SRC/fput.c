/*
    module  : fput.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fput  :  S X  ->  S
Writes X to stream S, pops X off stack.
*/
/* fput.c */
PRIVATE void fput_(void)
{
    FILE *stm;

    TWOPARAMS("fput");
#ifdef RUNTIME_CHECKS
    if (stk->next->op != FILE_ || !stk->next->u.fil)
	execerror("file", "fput");
#endif
    stm = stk->next->u.fil;
    writefactor(stk, stm);
    fprintf(stm, " ");
    POP(stk);
}
