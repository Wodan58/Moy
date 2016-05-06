/*
    module  : fopen.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
/* fopen.c */
PRIVATE void fopen_(void)
{
    TWOPARAMS("fopen");
    STRING("fopen");
    STRING2("fopen");
    if (OUTSIDE) {
	stk->next->u.fil = fopen(stk->next->u.str, stk->u.str);
	stk->next->op = FILE_;
	POP(stk);
    } else
	BINARY(FILE_NEWNODE, fopen(stk->next->u.str, stk->u.str));
}
