/*
    module  : pop.c
    version : 1.6
    date    : 07/02/18
*/

/**
pop  :  X  ->
Removes X from top of the stack.
*/
PRIVATE void do_pop(void)
{
#ifndef NCHECK
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("pop");
    POP(stk);
}
