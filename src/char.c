/*
    module  : char.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef CHAR_C
#define CHAR_C

/**
OK 2340  char  :  DA	X  ->  B
Tests whether X is a character.
*/
void char_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    node.u.num = node.op == CHAR_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
