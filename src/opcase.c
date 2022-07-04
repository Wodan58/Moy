/*
    module  : opcase.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef OPCASE_C
#define OPCASE_C

/**
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
PRIVATE void do_opcase(pEnv env)
{
    Node *cur, *node;

    TWOPARAMS("opcase");
    LIST("opcase");
    cur = env->stk->u.lis;
    CHECKEMPTYLIST(cur, "opcase");
    node = env->stk->next;
    for (; cur->next && cur->op == LIST_; cur = cur->next)
	if (cur->u.lis->op == node->op) {
	    if (cur->u.lis->op == USR_ || cur->u.lis->op == ANON_FUNCT_) {
		if (cur->u.lis->u.ptr == node->u.ptr)
		    break;
	    } else
		break;
	}
    CHECKLIST(cur->op, "opcase");
    cur = cur->next ? cur->u.lis->next : cur->u.lis;
    UNARY(LIST_NEWNODE, cur);
}
#endif
