/*
    module  : file.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef FILE_C
#define FILE_C

/**
Q0  OK  2400  file  :  DA  F  ->  B
[FOREIGN] Tests whether F is a file.
*/
void file_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    node.u.num = node.op == FILE_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
