/*
    module  : file.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FILE_C
#define FILE_C

/**
OK 2420  file  :  DA	F  ->  B
Tests whether F is a file.
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
