/*
    module  : frename.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
OK 1940  frename  :  DDA	P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
void frename_(pEnv env)
{
    Node node, path;

    PARM(2, FOPEN);
    path = vec_pop(env->stck);
    node = vec_pop(env->stck);
    node.u.num = !rename(node.u.str, path.u.str);
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
