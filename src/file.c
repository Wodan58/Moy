/*
    module  : file.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef FILE_C
#define FILE_C

/**
OK 2400  file  :  DA	F  ->  B
Tests whether F is a file.
*/
void file_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op == FILE_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
