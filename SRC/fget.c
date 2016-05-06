/*
    module  : fget.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fget  :  S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
/* fget.c */
PRIVATE void fget_(void)
{
    FILE *stm = 0;

    ONEPARAM("fget");
#ifdef RUNTIME_CHECKS
    if (stk->op != FILE_ || !stk->u.fil)
	execerror("file", "fget");
#endif
    stm = stk->u.fil;
    redirect(stm);
    getsym();
    readfactor();
}
