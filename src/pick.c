/*
    module  : pick.c
    version : 1.2
    date    : 07/02/18
*/

/**
pick  :  X Y Z 2  ->  X Y Z X
Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
PRIVATE void do_pick(void)
{
    int num;
    Node *look;

#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("pick");
    num = stk->u.num;
    POP(stk);
    for (look = stk; num--; look = look->next)
	;
    DUPLICATE(look);
}
