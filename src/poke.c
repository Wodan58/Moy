/*
    module  : poke.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef POKE_C
#define POKE_C

/**
poke  :  X Y Z 2  ->  Z Y
Updates the nth (e.g. 2) item X of the stack with the value on top of the stack.
*/
PRIVATE void do_poke(pEnv env)
{
    int num;
    Node *look;
    Operator op;
    YYSTYPE item;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("poke");
    num = env->stk->u.num;
    POP(env->stk);
    op = env->stk->op;
    item = env->stk->u;
    for (look = env->stk; num--; look = look->next)
	;
    look->op = op;
    look->u = item;
    POP(env->stk);
}
#endif
