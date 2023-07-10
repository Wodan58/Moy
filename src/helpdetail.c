/*
    module  : helpdetail.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

/**
OK 2940  helpdetail  :  D	[ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
void helpdetail_(pEnv env)
{
    Entry ent;
    int i, opcode;
    Node node, temp;

    PARM(1, HELP);
    node = vec_pop(env->stck);
    for (printf("\n"), i = vec_size(node.u.lis) - 1; i >= 0; i--) {
        temp = vec_at(node.u.lis, i);
        opcode = temp.op;
        if (opcode == USR_) {
            ent = sym_at(env->symtab, temp.u.ent);
            printf("%s  ==\n    ", ent.name);
            writeterm(env, ent.u.body);
	    printf("\n\n");
        } else {
            if (opcode == ANON_FUNCT_)
                opcode = operindex(temp.u.proc);
            if (opcode == BOOLEAN_)
                opcode = operindex(temp.u.num ? true_ : false_);
            if (opcode == INTEGER_ && temp.u.num == MAXINT)
                opcode = operindex(maxint_);
            printf("%s\t:  %s.\n%s\n", optable[opcode].name,
                optable[opcode].messg1, optable[opcode].messg2);
	    if (opcode <= FILE_)
		printf("\n");
        }
    }
}
#endif
