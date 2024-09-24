/*
    module  : undefs.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef UNDEFS_C
#define UNDEFS_C

/**
Q0  OK  1110  undefs  :  A  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
void undefs_(pEnv env)
{
    int i;
    Entry ent;
    Node node, elem;

    vec_init(node.u.lis);
    node.op = LIST_;
    elem.op = STRING_;
    for (i = vec_size(env->symtab) - 1; i; i--) {
	ent = vec_at(env->symtab, i);
	if (ent.name[0] && ent.name[0] != '_' && !ent.u.body) {
	    elem.u.str = ent.name;
	    vec_push(node.u.lis, elem);
	}
    }
    vec_push(env->stck, node);
}
#endif
