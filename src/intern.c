/*
    module  : intern.c
    version : 1.10
    date    : 04/11/24
*/
#ifndef INTERN_C
#define INTERN_C

/**
Q0  OK  2180  intern  :  DA  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
void intern_(pEnv env)
{
    Node node;
    int index;
    Entry ent;

    PARM(1, INTERN);
    env->stck = pvec_pop(env->stck, &node);
    index = lookup(env, node.u.str);
    ent = vec_at(env->symtab, index);
    if (ent.is_user) {
	node.op = USR_;
	node.u.ent = index;
    } else {
	node.op = ANON_FUNCT_;
	node.u.proc = ent.u.proc;
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
