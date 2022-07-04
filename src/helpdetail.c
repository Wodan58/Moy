/*
    module  : helpdetail.c
    version : 1.18
    date    : 06/20/22
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

#ifdef COMPILING
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
#ifdef COMPILING
    int i;
    Node *cur;
    char *name = "";

    COMPILE;
    ONEPARAM("helpdetail");
    LIST("helpdetail");
    for (printf("\n"), cur = env->stk->u.lis; cur; cur = cur->next) {
	i = cur->u.num;
	if (cur->op == USR_) {
	    name = dict_descr(env, cur);
	    if ((dict_flags(env, i) & IS_BUILTIN) == 0) {
		printf("%s  ==\n    ", name);
		writeterm(env, dict_body(env, i));
		printf("\n\n");
		continue;
	    }
	    i = search(name);
	} else if (cur->op > USR_ && cur->op <= FILE_) {
	    if (cur->op == BOOLEAN_)
		i = i ? search("true") : search("false");
	    else if (cur->op == INTEGER_ && cur->u.num == MAXINT_)
		i = search("maxint");
	    else
		i = cur->op;
	    name = optable[i].name;
	}
	printf("%s  :  %s.\n%s\n", name, optable[i].messg1, optable[i].messg2);
    }
    POP(env->stk);
#endif
}
#endif
