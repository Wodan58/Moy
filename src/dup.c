/*
    module  : dup.c
    version : 1.7
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_dup(void)
{
    TRACE;
    stk++;
    stk[-1] = stk[-2];
}
#else
/**
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
PRIVATE void do_dup(void)
{
#ifndef NCHECK
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("dup");
    DUPLICATE(stk);
}
#endif
