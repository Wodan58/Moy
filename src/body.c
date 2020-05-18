/*
    module  : body.c
    version : 1.12
    date    : 03/28/20
*/
#ifndef BODY_C
#define BODY_C

/**
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
PRIVATE void do_body(void)
{
    ONEPARAM("body");
#ifndef OLD_RUNTIME
    USERDEF("body");
    stk->u.lis = dict_body(stk->u.num);
    stk->op = LIST_;
#else
    POP(stk);
#endif
}
#endif
