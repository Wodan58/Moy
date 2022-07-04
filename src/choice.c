/*
    module  : choice.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef CHOICE_C
#define CHOICE_C

/**
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
PRIVATE void do_choice(pEnv env)
{
    THREEPARAMS("choice");
    if (env->stk->next->next->u.num)
	GTERNARY(env->stk->next->op, env->stk->next->u);
    else
	GTERNARY(env->stk->op, env->stk->u);
}
#endif
