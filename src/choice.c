/*
    module  : choice.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef CHOICE_C
#define CHOICE_C

/**
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
PRIVATE void do_choice(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("choice");
    if (env->stk->next->next->u.num) {
	env->stk->next->next->u = env->stk->next->u;
	env->stk->next->next->op = env->stk->next->op;
    } else {
	env->stk->next->next->u = env->stk->u;
	env->stk->next->next->op = env->stk->op;
    }
    POP(env->stk);
    POP(env->stk);
}
#endif
