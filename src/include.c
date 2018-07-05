/*
    module  : include.c
    version : 1.6
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_include(void)
{
    TRACE;
    include((char *)do_pop());
}
#else
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
#endif
