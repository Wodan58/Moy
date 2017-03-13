/*
    module  : fclose.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
PRIVATE void do_fclose(void)
{
    FILE *fp;

#ifndef NCHECK
    COMPILE;
    ONEPARAM("fclose");
    FILE("fclose");
#endif
    if ((fp = stk->u.fil) != 0)
	fclose(fp);
    POP(stk);
}
