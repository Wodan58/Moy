/*
    module  : file.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef FILE_C
#define FILE_C

/**
OK 2400  file  :  DA	F  ->  B
[FOREIGN] Tests whether F is a file.
*/
void file_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == FILE_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
