/*
    module  : pop.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef POP_C
#define POP_C

/**
pop  :  X  ->
Removes X from top of the stack.
*/
PRIVATE void do_pop(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("pop");
    POP(stk);
}
#endif
