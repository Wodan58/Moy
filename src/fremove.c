/*
    module  : fremove.c
    version : 1.4
    date    : 09/11/23
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
#ifndef COMPILER
    Node node;

    PARM(1, STRTOD);
    node = lst_pop(env->stck);
    node.u.num = !remove(node.u.str);
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
#endif
}
#endif
