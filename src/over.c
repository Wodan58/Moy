/*
    module  : over.c
    version : 1.3
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_over(void)
{
    TRACE;
    stk++;
    stk[-1] = stk[-3];
}
#else
/**
over  :  X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
PRIVATE void do_over(void)
{
#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("over");
    DUPLICATE(stk->next);
}
#endif
