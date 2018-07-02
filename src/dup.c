/*
    module  : dup.c
    version : 1.6
    date    : 07/02/18
*/

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
