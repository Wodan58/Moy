/*
    module  : char.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef CHAR_C
#define CHAR_C

/**
OK 2320  char  :  DA	X  ->  B
Tests whether X is a character.
*/
void char_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == CHAR_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
