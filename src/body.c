/*
    module  : body.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef BODY_X
#define BODY_C

#ifdef RUNTIME
void do_body(void)
{
    TRACE;
    do_push(0);
}
#else
/**
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
PRIVATE void do_body(void)
{
    ONEPARAM("body");
#ifndef NCHECK
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
