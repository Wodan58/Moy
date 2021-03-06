/*
    module  : helpdetail.c
    version : 1.17
    date    : 04/28/21
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

#ifndef OLD_RUNTIME
int search(char *name)
{
    int i;

    for (i = 0; optable[i].name; i++)
	if (!strcmp(name, optable[i].name))
	    return i;
    return 0;
}
#endif

/**
helpdetail  :  [ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
PRIVATE void do_helpdetail(pEnv env)
{
#ifndef OLD_RUNTIME
    int i;
    char *name;
    Node *node;

    COMPILE;
    ONEPARAM("HELP");
    LIST("HELP");
    for (printf("\n"), node = env->stk->u.lis; node; node = node->next) {
	i = node->u.num;
	if (node->op == USR_) {
	    name = dict_descr(env, i);
	    if ((dict_flags(env, i) & IS_BUILTIN) == 0) {
		printf("%s  ==\n    ", name);
		writeterm(env, dict_body(env, i), stdout);
		printf("\n\n");
		continue;
	    }
	    if ((i = search(name)) == 0)
		continue;
	} else if (node->op > USR_ && node->op < SYMBOL_) {
	    if (node->op == BOOLEAN_)
		i = i ? search("true") : search("false");
	    else if (node->op == INTEGER_ && node->u.num == MAXINT_)
		i = search("maxint");
	    else
		i = node->op;
	    name = optable[i].name;
	} else
	    continue;
	printf("%s  :  %s.\n%s\n", name, optable[i].messg1, optable[i].messg2);
    }
    POP(env->stk);
#endif
}
#endif
