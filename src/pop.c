/*
    module  : pop.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef POP_X
#define POP_C

#ifdef RUNTIME
node_t do_pop(void)
{
#ifdef VECTOR
    node_t *node;

    node = vec_pop(theStack);
    return *node;
#else
    return *--stk;
#endif
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
#endif
