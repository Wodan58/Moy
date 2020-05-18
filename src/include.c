/*
    module  : include.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef INCLUDE_C
#define INCLUDE_C

/**
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
PRIVATE void do_include(void)
{
    char *str;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("include");
    STRING("include");
    str = stk->u.str;
    POP(stk);
    include(str);
}
#endif
