/*
    module  : include.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
PRIVATE void do_include(void)
{
    char *str;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("include");
    STRING("include");
#endif
    str = stk->u.str;
    POP(stk);
    include(str);
}
