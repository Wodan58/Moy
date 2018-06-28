/*
    module  : helpdetail.c
    version : 1.9
    date    : 06/28/18
*/
#include "runtime.h"

extern optable_t optable[];

/**
helpdetail  :  [ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
PRIVATE void do_helpdetail(void)
{
#ifndef NCHECK
    int i;
    char *name;
    Node *node;
    Operator op;

    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("HELP");
    LIST("HELP");
    printf("\n");
    node = stk->u.lis;
    while (node) {
	if (node->op == USR_) {
	    i = node->u.num;
	    name = dict_descr(i);
	    printf("%s  ==\n    ", name);
	    writeterm(dict_body(i), stdout);
	    printf("\n\n");
	    break;
	} else {
	    if ((op = node->op) == BOOLEAN_)
		op = node->u.num ? DO_TRUE : DO_FALSE;
	    if (op == INTEGER_ && node->u.num == MAXINT_)
		op = DO_MAXINT;
	    name = opername(op);
	    for (i = 0; optable[i].name; i++)
		if (!strcmp(name, optable[i].name))
		    printf("%s  :  %s.\n%s\n", name, optable[i].messg1,
			   optable[i].messg2);
	}
	node = node->next;
    }
    POP(stk);
#endif
}
