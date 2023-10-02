/*
    module  : body.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef BODY_C
#define BODY_C

/**
OK 2190  body  :  DA	U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
void body_(pEnv env)
{
    Node node;
    Entry ent;

    PARM(1, BODY);
    env->stck = pvec_pop(env->stck, &node);
    ent = vec_at(env->symtab, node.u.ent);
    node.u.lis = ent.u.body;
    node.op = LIST_;
    env->stck = pvec_add(env->stck, node);
}
#endif
