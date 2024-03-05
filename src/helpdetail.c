/*
    module  : helpdetail.c
    version : 1.11
    date    : 03/05/24
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

/**
Q0  OK  2920  helpdetail  :  D  [ S1 S2 .. ]  ->
[IMPURE] Gives brief help on each symbol S in the list.
*/
void helpdetail_(pEnv env)
{
    Entry ent;
    OpTable *tab;
    int i, opcode;
    Node node, temp;

    PARM(1, HELP);
    env->stck = pvec_pop(env->stck, &node);
    if (env->ignore)
	return;
    for (printf("\n"), i = pvec_cnt(node.u.lis) - 1; i >= 0; i--) {
	temp = pvec_nth(node.u.lis, i);
	if ((opcode = temp.op) == USR_) {
	    ent = vec_at(env->symtab, temp.u.ent);
	    printf("%s  ==\n    ", ent.name);
	    writeterm(env, ent.u.body, stdout);
	    printf("\n\n");
	} else {
	    if (opcode == ANON_FUNCT_) {
		if (env->bytecoding || env->compiling)
		    opcode = temp.u.ent;
	        else
		    opcode = operindex(env, temp.u.proc);
	    }
	    if (opcode == BOOLEAN_)
		opcode = operindex(env, temp.u.num ? true_ : false_);
	    if (opcode == INTEGER_ && temp.u.num == MAXINT_)
		opcode = operindex(env, maxint_);
	    tab = readtable(opcode);
	    printf("%s\t:  %s.\n%s\n", tab->name, tab->messg1, tab->messg2);
	    if (opcode <= BIGNUM_)
		printf("\n");
	}
    }
}
#endif
