/*
    module  : helpdetail.c
    version : 1.12
    date    : 03/21/24
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
    env->stck = pvec_pop(env->stck, &node);
    printf("\n");
    for (i = pvec_cnt(node.u.lis) - 1; i >= 0; i--) {
	temp = pvec_nth(node.u.lis, i);
	if ((op = temp.op) == USR_) {
	    ent = vec_at(env->symtab, temp.u.ent);
	    printf("%s  ==\n    ", ent.name);
	    writeterm(env, ent.u.body, stdout);
	    printf("\n\n");
	} else {
	    if (op == ANON_FUNCT_) {
		if (env->bytecoding || env->compiling)
		    op = temp.u.ent;
	        else
		    op = operindex(env, temp.u.proc);
	    }
	    else if (op == BOOLEAN_)
		op = operindex(env, temp.u.num ? true_ : false_);
	    else if (op == INTEGER_ && temp.u.num == MAXINT_)
		op = operindex(env, maxint_);
	    else if (op == FILE_) {
		if (temp.u.fil == stdin)
		    op = operindex(env, stdin_);
		else if (temp.u.fil == stdout)
		    op = operindex(env, stdout_);
		else if (temp.u.fil == stderr)
		    op = operindex(env, stderr_);
	    }
	    printf("%s\t:  %s.\n%s\n", optable[op].name, optable[op].messg1,
			    optable[op].messg2);
	    if (op <= BIGNUM_)
		printf("\n");
	}
    }
}
#endif
