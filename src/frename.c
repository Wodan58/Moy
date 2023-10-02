/*
    module  : frename.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
OK 1930  frename  :  DDA	P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
void frename_(pEnv env)
{
    Node node, path;

    PARM(2, FOPEN);
    env->stck = pvec_pop(env->stck, &path);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = !rename(node.u.str, path.u.str);
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
