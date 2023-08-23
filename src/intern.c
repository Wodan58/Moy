/*
    module  : intern.c
    version : 1.2
    date    : 08/23/23
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
    node = lst_pop(env->stck);
    lookup(env, node.u.str);
    ent = vec_at(env->symtab, env->location);
    if (ent.is_user) {
        node.op = USR_;
        node.u.ent = env->location;
    } else {
        node.op = ANON_FUNCT_;
        node.u.proc = ent.u.proc;
    }
    lst_push(env->stck, node);
}
#endif
