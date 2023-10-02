/*
    module  : fremove.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
OK 1920  fremove  :  DA	P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
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
