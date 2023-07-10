/*
    module  : intern.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef INTERN_C
#define INTERN_C

/**
OK 2190  intern  :  DA	"sym"  ->  sym
Pushes the item whose name is "sym".
*/
PRIVATE void intern_(pEnv env)
{
    Node node;
    Entry ent;

    PARM(1, INTERN);
    node = vec_pop(env->stck);
    lookup(env, node.u.str);
    ent = sym_at(env->symtab, env->location);
    if (ent.is_user) {
        node.op = USR_;
        node.u.ent = env->location;
    } else {
        node.op = ANON_FUNCT_;
        node.u.proc = ent.u.proc;
    }
    vec_push(env->stck, node);
}
#endif
