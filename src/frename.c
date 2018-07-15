/*
    module  : frename.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FRENAME_X
#define FRENAME_C

#ifdef NEW_RUNTIME
void do_frename(void)
{
    TRACE;
    stk[-2] = !rename((char *)stk[-2], (char *)stk[-1]);
    (void)do_pop();
}
#else
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
    if (OUTSIDE) {
	stk->next->u.num = !rename(stk->next->u.str, stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, !rename(stk->next->u.str, stk->u.str));
}
#endif
#endif
