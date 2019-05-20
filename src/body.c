/*
    module  : body.c
    version : 1.11
    date    : 05/16/19
*/
#ifndef BODY_X
#define BODY_C

#ifdef NEW_RUNTIME
void do_body(void)
{
#error "body" is not supported in the new version
}
#else
/**
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
PRIVATE void do_body(void)
{
    ONEPARAM("body");
#ifndef OLD_RUNTIME
    USERDEF("body");
    if (OUTSIDE) {
	stk->u.lis = dict_body(stk->u.num);
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, dict_body(stk->u.num));
#else
    POP(stk);
#endif
}
#endif
#endif
