/*
    module  : fopen.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FOPEN_C
#define FOPEN_C

/**
OK 1900  fopen  :  DDA	P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
void fopen_(pEnv env)
{
    Node path, mode, node;

    PARM(2, FOPEN);
    mode = vec_pop(env->stck);
    path = vec_pop(env->stck);
    node.u.fil = fopen(path.u.str, mode.u.str);
    node.op = FILE_;
    vec_push(env->stck, node);
}
#endif
