/*
    module  : over.c
    version : 1.4
    date    : 07/10/18
*/
#ifndef OVER_X
#define OVER_C

#ifdef RUNTIME
void do_over(void)
{
    TRACE;
    do_push(stk[-2]);
#if 0
    stk++;
    stk[-1] = stk[-3];
#endif
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
#endif
