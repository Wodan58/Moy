/*
    module  : getenv.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
/* getenv.c */
PRIVATE void getenv_(void)
{
    ONEPARAM("getenv");
    STRING("getenv");
    if (OUTSIDE)
	stk->u.str = getenv(stk->u.str);
    else
	UNARY(STRING_NEWNODE, getenv(stk->u.str));
}
