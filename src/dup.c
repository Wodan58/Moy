/*
    module  : dup.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef DUP_X
#define DUP_C

#ifdef NEW_RUNTIME
void do_dup(void)
{
    TRACE;
    do_push(stk[-1]);
}
#else
/**
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
PRIVATE void do_dup(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("dup");
    DUPLICATE(stk);
}
#endif
#endif
