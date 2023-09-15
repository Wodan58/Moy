/*
    module  : body.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    ent = vec_at(env->symtab, node.u.ent);
    node.u.lis = ent.u.body;
    node.op = LIST_;
    lst_push(env->stck, node);
}
#endif
