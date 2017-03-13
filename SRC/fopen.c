/*
    module  : fopen.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
PRIVATE void do_fopen(void)
{
#ifndef NCHECK
    COMPILE;
    TWOPARAMS("fopen");
    STRING("fopen");
    STRING2("fopen");
#endif
    if (OUTSIDE) {
	stk->next->u.fil = fopen(stk->next->u.str, stk->u.str);
	stk->next->op = FILE_;
	POP(stk);
    } else
	BINARY(FILE_NEWNODE, fopen(stk->next->u.str, stk->u.str));
}
