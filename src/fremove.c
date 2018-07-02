/*
    module  : fremove.c
    version : 1.6
    date    : 07/02/18
*/

/**
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
PRIVATE void do_fremove(void)
{
#ifndef NCHECK
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
