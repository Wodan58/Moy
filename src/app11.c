/*
    module  : app11.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef APP11_X
#define APP11_C

#ifndef APP1_C
#undef APP1_X
#include "app1.c"
#define APP1_X
#endif

#ifdef NEW_RUNTIME

#ifndef POPD_C
#undef POPD_X
#include "popd.c"
#define POPD_X
#endif

void do_app11(void)
{
    TRACE;
    do_app1();
    do_popd();
}
#else
/**
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
PRIVATE void do_app11(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    THREEPARAMS("app11");
    ONEQUOTE("app11");
    do_app1();
    stk->next = stk->next->next;
}
#endif
#endif
