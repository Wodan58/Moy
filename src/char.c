/*
    module  : char.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    node.u.num = node.op == CHAR_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
