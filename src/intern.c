/*
    module  : intern.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef INTERN_C
#define INTERN_C

/**
OK 2180  intern  :  DA	"sym"  ->  sym
Pushes the item whose name is "sym".
*/
PRIVATE void intern_(pEnv env)
{
    Node node;
    Entry ent;

    PARM(1, INTERN);
    env->stck = pvec_pop(env->stck, &node);
    lookup(env, node.u.str);
    ent = vec_at(env->symtab, env->location);
    if (ent.is_user) {
	node.op = USR_;
	node.u.ent = env->location;
    } else {
	node.op = ANON_FUNCT_;
	node.u.proc = ent.u.proc;
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
