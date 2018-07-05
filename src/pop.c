/*
    module  : pop.c
    version : 1.7
    date    : 07/05/18
*/
#ifdef RUNTIME
node_t do_pop(void)
{
    return *--stk;
}
#else
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
#endif
