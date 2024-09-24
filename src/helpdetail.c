/*
    module  : helpdetail.c
    version : 1.14
    date    : 09/17/24
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

/**
Q0  IGNORE_POP  2920  helpdetail  :  D  [ S1 S2 .. ]  ->
[IMPURE] Gives brief help on each symbol S in the list.
*/
void helpdetail_(pEnv env)
{
    Entry ent;
    int i, op;
    Node node, temp;

    PARM(1, HELP);
    node = vec_pop(env->stck);
    printf("\n");
    for (i = vec_size(node.u.lis) - 1; i >= 0; i--) {
	temp = vec_at(node.u.lis, i);
	switch (op = temp.op) {
	case USR_:
	    ent = vec_at(env->symtab, temp.u.ent);
	    printf("%s  ==\n    ", ent.name);
	    writeterm(env, ent.u.body, stdout);
	    printf("\n\n");
	    continue;

	case ANON_FUNCT_:
	    op = operindex(env, temp.u.proc);
	    break;

	case BOOLEAN_:
	    op = operindex(env, temp.u.num ? true_ : false_);
	    break;

	case INTEGER_:
	    if (temp.u.num == MAXINT_)
		op = operindex(env, maxint_);
	    break;

	case FILE_:
	    if (temp.u.fil == stdin)
		op = operindex(env, stdin_);
	    else if (temp.u.fil == stdout)
		op = operindex(env, stdout_);
	    else if (temp.u.fil == stderr)
		op = operindex(env, stderr_);
	    break;
	}
	printf("%s\t:  %s.\n%s\n", optable[op].name, optable[op].messg1,
		optable[op].messg2);
	if (op <= BIGNUM_)
	    printf("\n");
    }
}
#endif
