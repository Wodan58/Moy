/*
    module  : fremove.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
OK 1930  fremove  :  DA	P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
void fremove_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = vec_pop(env->stck);
    node.u.num = !remove(node.u.str);
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
