/*
    module  : fremove.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef FREMOVE_X
#define FREMOVE_C

#ifdef NEW_RUNTIME
void do_fremove(void)
{
    TRACE;
    stk[-2] = !remove((char *)stk[-1]);
    (void)do_pop();
}
#else
/**
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
PRIVATE void do_fremove(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fremove");
    STRING("fremove");
    if (OUTSIDE) {
	stk->next->u.num = !remove(stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	UNARY(BOOLEAN_NEWNODE, !remove(stk->u.str));
}
#endif
#endif
