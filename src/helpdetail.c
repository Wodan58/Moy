/*
    module  : helpdetail.c
    version : 1.11
    date    : 07/02/18
*/

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
    unsigned flags;

    COMPILE;
    ONEPARAM("HELP");
    LIST("HELP");
    printf("\n");
    node = stk->u.lis;
    for (node = stk->u.lis; node; node = node->next) {
	if (node->op == USR_) {
	    i = node->u.num;
	    flags = dict_flags(i);
	    name = dict_descr(i);
	    if ((flags & IS_BUILTIN) == 0) {
		printf("%s  ==\n    ", name);
		writeterm(dict_body(i), stdout);
		printf("\n\n");
		continue;
	    }
	    for (i = 0; optable[i].name; i++)
		if (!strcmp(name, optable[i].name))
		    break;
	} else if (node->op > USR_ && node->op < SYMBOL_)
	    i = node->op;
	else
	    continue;
	printf("%s  :  %s.\n%s\n", name, optable[i].messg1, optable[i].messg2);
    }
    POP(stk);
#endif
}
