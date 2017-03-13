/*
    module  : include.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
PRIVATE void do_include(void)
{
    char *str;

#ifndef NCHECK
    COMPILE;
    ONEPARAM("include");
    STRING("include");
#endif
    str = stk->u.str;
    POP(stk);
    include(str);
}
