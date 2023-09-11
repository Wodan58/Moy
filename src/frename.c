/*
    module  : frename.c
    version : 1.4
    date    : 09/11/23
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
#ifndef COMPILER
    Node node, path;

    PARM(2, FOPEN);
    path = lst_pop(env->stck);
    node = lst_pop(env->stck);
    node.u.num = !rename(node.u.str, path.u.str);
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
#endif
}
#endif
