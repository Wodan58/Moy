/*
    module  : over.c
    version : 1.5
    date    : 07/15/18
*/
#ifndef OVER_X
#define OVER_C

#ifdef NEW_RUNTIME
void do_over(void)
{
    TRACE;
    do_push(stk[-2]);
}
#else
/**
over  :  X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
PRIVATE void do_over(void)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("over");
    DUPLICATE(stk->next);
}
#endif
#endif
