/*
    module  : helpdetail.c
    version : 1.7
    date    : 06/25/18
*/
#include "runtime.h"

extern optable_t optable[];

/**
helpdetail  :  [ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
PRIVATE void do_helpdetail(void)
{
    Node *node;
    Operator op;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("HELP");
    LIST("HELP");
#endif
    printf("\n");
    node = stk->u.lis;
    while (node) {
	if (node->op == USR_) {
	    printf("%s  ==\n    ", node->u.ent->name);
	    writeterm(node->u.ent->u.body, stdout);
	    printf("\n");
	    break;
	} else {
	    if ((op = node->op) == BOOLEAN_)
		op = node->u.num ? DO_TRUE : DO_FALSE;
	    if (op == INTEGER_ && node->u.num == MAXINT_)
		op = DO_MAXINT;
	    printf("%s  :  %s.\n%s\n", optable[op].name,
		   optable[op].messg1, optable[op].messg2);
	}
	printf("\n");
	node = node->next;
    }
    POP(stk);
}
