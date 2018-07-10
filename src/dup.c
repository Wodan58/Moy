/*
    module  : dup.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef DUP_X
#define DUP_C

#ifdef RUNTIME
void do_dup(void)
{
    TRACE;
    do_push(stk[-1]);
#if 0
    stk++;
    stk[-1] = stk[-2];
#endif
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
#endif
