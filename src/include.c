/*
    module  : include.c
    version : 1.5
    date    : 07/02/18
*/

/**
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
PRIVATE void do_include(void)
{
    char *str;

#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("include");
    STRING("include");
    str = stk->u.str;
    POP(stk);
    include(str);
}
