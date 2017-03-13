/*
    module  : fget.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
fget  :  S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
PRIVATE void do_fget(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("fget");
    if (stk->op != FILE_ || !stk->u.fil)
	execerror("file", "fget");
#endif
    redirect(stk->u.fil);
    readfactor(yylex());
}
