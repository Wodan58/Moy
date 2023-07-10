/*
    module  : sametype.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

/**
OK 2320  sametype  :  DDA	X Y  ->  B
Tests whether X and Y have the same type.
*/
void sametype_(pEnv env)
{
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    if (first.op == ANON_FUNCT_)
        node.u.num = first.u.proc == second.u.proc;
    else
        node.u.num = first.op == second.op;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
