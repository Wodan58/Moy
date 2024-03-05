/*
    module  : fremove.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
Q0  OK  1920  fremove  :  DA  P  ->  B
[FOREIGN] The file system object with pathname P is removed from the file
system. B is a boolean indicating success or failure.
*/
void fremove_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = !remove(node.u.str);
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
