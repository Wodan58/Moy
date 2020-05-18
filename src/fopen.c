/*
    module  : fopen.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef FOPEN_C
#define FOPEN_C

/**
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
PRIVATE void do_fopen(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fopen");
    STRING("fopen");
    STRING2("fopen");
    stk->next->u.fil = fopen(stk->next->u.str, stk->u.str);
    stk->next->op = FILE_;
    POP(stk);
}
#endif
