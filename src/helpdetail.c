/*
    module  : helpdetail.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

/**
OK 2920  helpdetail  :  D	[ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
void helpdetail_(pEnv env)
{
    Entry ent;
    OpTable *tab;
    int i, opcode;
    Node node, temp;

    PARM(1, HELP);
    node = lst_pop(env->stck);
    for (printf("\n"), i = lst_size(node.u.lis) - 1; i >= 0; i--) {
	temp = lst_at(node.u.lis, i);
	opcode = temp.op;
	if (opcode == USR_) {
	    ent = vec_at(env->symtab, temp.u.ent);
	    printf("%s  ==\n    ", ent.name);
	    writeterm(env, ent.u.body, stdout);
	    printf("\n\n");
	} else {
	    if (opcode == ANON_FUNCT_)
		opcode = operindex(temp.u.proc);
	    if (opcode == BOOLEAN_)
		opcode = operindex(temp.u.num ? true_ : false_);
	    if (opcode == INTEGER_ && temp.u.num == MAXINT)
		opcode = operindex(maxint_);
	    tab = readtable(opcode);
	    printf("%s\t:  %s.\n%s\n", tab->name, tab->messg1, tab->messg2);
	    if (opcode <= ANON_PRIME_)
		printf("\n");
	}
    }
}
#endif
