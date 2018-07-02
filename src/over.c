/*
    module  : over.c
    version : 1.2
    date    : 07/02/18
*/

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
