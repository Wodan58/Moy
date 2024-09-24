/*
    module  : frename.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
Q0  OK  1930  frename  :  DDA  P1 P2  ->  B
[FOREIGN] The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
void frename_(pEnv env)
{
    Node path, node;

    PARM(2, FOPEN);
    path = vec_pop(env->stck);
    node = vec_pop(env->stck);
    node.u.num = !rename(node.u.str, path.u.str);
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
