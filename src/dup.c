/*
    module  : dup.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef DUP_C
#define DUP_C

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
