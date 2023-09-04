/*
    module  : integer.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef INTEGER_C
#define INTEGER_C

/**
OK 2310  integer  :  DA	X  ->  B
Tests whether X is an integer.
*/
void integer_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op == INTEGER_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
