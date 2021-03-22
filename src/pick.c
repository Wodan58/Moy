/*
    module  : pick.c
    version : 1.7
    date    : 03/15/21
*/
#ifndef PICK_C
#define PICK_C

/**
pick  :  X Y Z 2  ->  X Y Z X
Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
PRIVATE void do_pick(pEnv env)
{
    int num;
    Node *look;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("pick");
    num = env->stk->u.num;
    POP(env->stk);
    for (look = env->stk; num--; look = look->next)
	;
    DUPLICATE(look);
}
#endif
