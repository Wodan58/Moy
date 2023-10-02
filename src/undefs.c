/*
    module  : undefs.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef UNDEFS_C
#define UNDEFS_C

/**
OK 1110  undefs  :  A	->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
void undefs_(pEnv env)
{
    int i;
    Entry ent;
    Node node, elem;

    node.u.lis = pvec_init();
    node.op = LIST_;
    elem.op = STRING_;
    for (i = vec_size(env->symtab) - 1; i; i--) {
	ent = vec_at(env->symtab, i);
	if (ent.name[0] && ent.name[0] != '_' && !ent.u.body) {
	    elem.u.str = ent.name;
	    node.u.lis = pvec_add(node.u.lis, elem);
	}
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
