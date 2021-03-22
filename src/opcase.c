/*
    module  : opcase.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef OPCASE_C
#define OPCASE_C

/**
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
PRIVATE void do_opcase(pEnv env)
{
    Node *cur;

#ifndef OLD_RUNTIME
    if (compiling && LIST_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    ONEPARAM("opcase");
    LIST("opcase");
    CHECKEMPTYLIST(env->stk->u.lis, "opcase");
    for (cur = env->stk->u.lis; cur->next && cur->op == LIST_; cur = cur->next) {
	if (cur->u.lis->op == env->stk->next->op)
	    if (cur->u.lis->op == USR_ || cur->u.lis->op == ANON_FUNCT_) {
		if (cur->u.lis->u.ptr == env->stk->next->u.ptr)
		    break;
	    } else
		break;
    }
    CHECKLIST(cur->op, "opcase");
    cur = cur->next ? cur->u.lis->next : cur->u.lis;
    env->stk->u.lis = cur;
    env->stk->op = LIST_;
}
#endif
