/*
    module  : fclose.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
/* fclose.c */
PRIVATE void fclose_(void)
{
    ONEPARAM("fclose");
    FILE("fclose");
    if (stk->u.fil)
	fclose(stk->u.fil);
    POP(stk);
}
