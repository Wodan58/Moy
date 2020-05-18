/*
    module  : frename.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
frename  :  P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
PRIVATE void do_frename(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("frename");
    STRING("frename");
    STRING2("frename");
    stk->next->u.num = !rename(stk->next->u.str, stk->u.str);
    stk->next->op = BOOLEAN_;
    POP(stk);
}
#endif
