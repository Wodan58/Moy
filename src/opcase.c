/*
    module  : opcase.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef OPCASE_X
#define OPCASE_C

#ifdef NEW_RUNTIME
void do_opcase(void)
{
    TRACE;
    do_push(0);
}
#else
/**
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
PRIVATE void do_opcase(void)
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
    CHECKEMPTYLIST(stk->u.lis, "opcase");
    for (cur = stk->u.lis; cur->next && cur->op == LIST_; cur = cur->next) {
	if (cur->u.lis->op == stk->next->op)
	    if (cur->u.lis->op == USR_ || cur->u.lis->op == ANON_FUNCT_) {
		if (cur->u.lis->u.ptr == stk->next->u.ptr)
		    break;
	    } else
		break;
    }
    CHECKLIST(cur->op, "opcase");
    cur = cur->next ? cur->u.lis->next : cur->u.lis;
    if (OUTSIDE) {
	stk->u.lis = cur;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, cur);
}
#endif
#endif
